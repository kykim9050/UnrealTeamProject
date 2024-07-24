// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestPlayerController.h"
#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "TestLevel/Item/WeaponBase.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "MainGameLevel/Object/MapObjectBase.h"

#include "TestLevel/UI/TestPlayHUD.h"
#include "TestLevel/UI/TestHpBarUserWidget.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "MainGameLevel/Object/Bomb.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 67.0f));
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = true;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	// MinimapIcon Component
	MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	MinimapIconComponent->SetupAttachment(RootComponent);
	MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// Character Mesh
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bHiddenInSceneCapture = true;

	// FPV Character Mesh
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// Riding Character Mesh => 메인캐릭터로 이전해야 함 (새로 추가됨)
	RidingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RidingMesh"));
	RidingMesh->SetupAttachment(GetMesh());
	RidingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	RidingMesh->SetVisibility(false);
	RidingMesh->SetIsReplicated(true);
	RidingMesh->bHiddenInSceneCapture = true;

	// Item Mesh => 메인캐릭터로 이전해야 함 (새로 추가됨)
	ItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSocketMesh"));
	ItemSocketMesh->SetupAttachment(GetMesh(), FName("ItemSocket"));
	ItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ItemSocketMesh->SetGenerateOverlapEvents(true);
	ItemSocketMesh->SetOwnerNoSee(true);
	ItemSocketMesh->SetVisibility(false);
	ItemSocketMesh->SetIsReplicated(true);
	ItemSocketMesh->bHiddenInSceneCapture = true;

	// FPV Item Mesh => 메인캐릭터로 이전해야 함 (새로 추가됨)
	FPVItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FPVItemSocketMesh"));
	FPVItemSocketMesh->SetupAttachment(FPVMesh, FName("FPVItemSocket"));
	FPVItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	FPVItemSocketMesh->SetGenerateOverlapEvents(true);
	FPVItemSocketMesh->SetOnlyOwnerSee(true);
	FPVItemSocketMesh->SetVisibility(false);
	FPVItemSocketMesh->SetIsReplicated(true);
	FPVItemSocketMesh->bCastDynamicShadow = false;
	FPVItemSocketMesh->CastShadow = false;

	// Map Item 검사
	GetMapItemCollisonComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("GetMapItemCollisionComponent"));
	GetMapItemCollisonComponent->SetupAttachment(RootComponent);
	GetMapItemCollisonComponent->SetRelativeLocation(FVector(100.0, 0.0, -20.0f));
	GetMapItemCollisonComponent->SetCollisionProfileName(FName("MapItemSearch"));

	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		// Inventory (for UI Test)
		FItemInformation NewSlot;
		/*NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;*/
		ItemSlot.Push(NewSlot);
		IsItemIn.Push(false);
	}

	// HandAttack Component
	//FString Name = "Punch";
	HandAttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hand Attack Comp"));
	//HandAttackComponent->SetupAttachment(GetMesh(), *Name);
	HandAttackComponent->SetupAttachment(GetMesh());
	HandAttackComponent->SetRelativeLocation({ 0.0f, 80.0f, 120.0f });
	//HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void ATestCharacter::CharacterPlayerToDropItem_Implementation()	// => 메인캐릭터로 이전해야 함 (24.07.23 수정됨)
{
	// DropItem 할 수 없는 경우 1: 맨손일 때
	if (CurItemIndex == -1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("There's no item to drop. (Current posture is 'Barehand')")));
		return;
	}

	// DropItem 할 수 없는 경우 2: (그럴리는 없겠지만) 현재 Posture에 해당하는 무기가 인벤토리에 없을 때
	if (IsItemIn[CurItemIndex] == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("There's no item to drop. (The item slot is empty)")));
		return;
	}

	// 떨어트릴 아이템을 Actor로 생성
	FName ItemName = ItemSlot[CurItemIndex].Name;
	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FItemDataRow* ItemBase = MainGameInst->GetItemData(ItemName);
	FTransform BoneTrans = GetMesh()->GetBoneTransform(FName("weapon_r"), ERelativeTransformSpace::RTS_World);

	AActor* DropItem = GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), BoneTrans);

	// 아이템을 앞으로 던지기 (미완)
	//GetMesh()->SetSimulatePhysics(true);
	FVector ImpulseVector = GetActorForwardVector() * 1000.0f;
	GetMesh()->AddImpulse(ImpulseVector, FName("weapon_r"), false);

	// 손에 들고 있던 아이템을 인벤토리에서 삭제
	FItemInformation NewSlot;
	ItemSlot[CurItemIndex] = NewSlot;
	IsItemIn[CurItemIndex] = false;

	// 자세를 맨손으로 변경
	ChangePosture(EPlayerPosture::Barehand);
}

//void ATestCharacter::Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
//{
//	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
//	if (nullptr == Monster)
//	{
//		return;
//	}
//}

void ATestCharacter::HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
	if (nullptr == Monster)
	{
		return;
	}

	Monster->Damaged(150.0f);
}

void ATestCharacter::ChangeHandAttackCollisionProfile(FName _Name)
{
	HandAttackComponent->SetCollisionProfileName(_Name);
}

void ATestCharacter::GetDamage(float _Damage)
{
	PlayerHp -= _Damage;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	NetCheck();
	Super::BeginPlay();

	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	// 몽타주 변경에 필요한 세팅 추가 필요 (태환)
	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	FPVPlayerAnimInst = Cast<UPlayerAnimInstance>(FPVMesh->GetAnimInstance());

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
	//UISetting();
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerHp(DeltaTime);

	//DefaultRayCast(DeltaTime);
	//TArray<FItemInformation> I = ItemSlot;
	//AGameModeBase* Ptr = GetWorld()->GetAuthGameMode();
}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestCharacter, StateValue);
	DOREPLIFETIME(ATestCharacter, PostureValue);
	DOREPLIFETIME(ATestCharacter, RayCastToItemName);

	// HP (for UI, Monster test)
	DOREPLIFETIME(ATestCharacter, PlayerHp);

	// LowerState (태환)
	DOREPLIFETIME(ATestCharacter, LowerStateValue);
	DOREPLIFETIME(ATestCharacter, DirValue);

	DOREPLIFETIME(ATestCharacter, Token);
}

//void ATestCharacter::TestRayCast(float _DeltaTime, FVector _StartPos, FVector _EndPos, FRotator _CameraRot)
//{
//	FVector Start = GetActorLocation();
//	Start.X += _StartPos.X;
//	Start.Y += _StartPos.Y;
//	Start.Z += _StartPos.Z;
//
//	CameraComponent->AddLocalRotation(_CameraRot);
//	FVector ForwardVector = CameraComponent->GetForwardVector();
//
//	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));
//
//	FVector End = Start + (ForwardVector * 1000);
//
//	FHitResult Hit;
//	if (GetWorld())
//	{
//		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, FCollisionQueryParams(), FCollisionResponseParams());
//		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0.0f, 0.0f);
//		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, _DeltaTime, 0.0f, 0.0f);
//
//		if (true == ActorHit && Hit.GetActor())
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, Hit.GetActor()->GetFName().ToString());
//			//Hit.GetActor()->ActorHasTag(TEXT(""));
//			//AActor* GetActorTest = Hit.GetActor();
//			GetMapItem = Hit.GetActor();
//			int TagCount = Hit.GetActor()->Tags.Num();
//			if (0 != TagCount)
//			{
//				for (size_t i = 0; i < Hit.GetActor()->Tags.Num(); i++)
//				{
//					FString TagName = Hit.GetActor()->Tags[i].ToString();
//					RayCastToItemName = TagName;
//					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TagName);
//				}
//			}
//		}
//		else
//		{
//			GetMapItem = nullptr;
//			RayCastToItemName = "";
//		}
//	}
//}
//
//void ATestCharacter::DefaultRayCast(float _DeltaTime)
//{
//	FVector Start = GetActorLocation();
//	FVector ForwardVector = CameraComponent->GetForwardVector();
//	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));
//	FVector End = Start + (ForwardVector * 1000);
//
//	// 아이템 줍기.
//	FHitResult Hit;
//	if (GetWorld())
//	{
//		// 아이템 콜리전 충돌.
//		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, FCollisionQueryParams(), FCollisionResponseParams());
//		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, _DeltaTime, 0.0f, 0.0f);
//
//		if (true == ActorHit && Hit.GetActor())
//		{
//			GetMapItem = Hit.GetActor();
//			int TagCount = Hit.GetActor()->Tags.Num();
//			if (0 != TagCount)
//			{
//				for (size_t i = 0; i < Hit.GetActor()->Tags.Num(); i++)
//				{
//					FString TagName = Hit.GetActor()->Tags[i].ToString();
//					RayCastToItemName = TagName;
//					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TagName);
//				}
//			}
//		}
//		else
//		{
//			GetMapItem = nullptr;
//			RayCastToItemName = "";
//		}
//	}
//}

void ATestCharacter::FireRayCast_Implementation(float _DeltaTime)	// => 메인캐릭터로 이전해야 함 (내용 수정됨)
{
	if (CurItemIndex == -1 || ItemSlot[CurItemIndex].ReloadMaxNum == -1)
	{
		return;
	}

	if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	{
		ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	}

	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	FVector Start = GetMesh()->GetSocketLocation(FName("weapon_r_muzzle"));
	Start.Z -= 20.0f;
	FVector End = (Con->GetControlRotation().Vector() * 2000.0f) + Start;
	FHitResult Hit;

	if (GetWorld())
	{
		ItemSlot[CurItemIndex].ReloadLeftNum -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Bullet left : %d / %d"), ItemSlot[CurItemIndex].ReloadLeftNum, ItemSlot[CurItemIndex].ReloadMaxNum));

		//bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel9, FCollisionQueryParams(), FCollisionResponseParams());
		TArray<AActor*> IgnoreActors;
		bool ActorHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0.0f, 0.0f);

		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			FString BoneName = Hit.BoneName.ToString();
			UE_LOG(LogTemp, Warning, TEXT("Bone Name : %s"), *BoneName);
			ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Hit.GetActor());
			if (nullptr != Monster)
			{
				Monster->Damaged(ItemSlot[CurItemIndex].Damage);
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : %d"), *Monster->GetName(), ItemSlot[CurItemIndex].Damage));
			}
		}
	}
}

void ATestCharacter::ChangeMontage_Implementation()
{
	PlayerAnimInst->ChangeAnimation(PostureValue);
	FPVPlayerAnimInst->ChangeAnimation(PostureValue);
	ClientChangeMontage();
}

void ATestCharacter::ClientChangeMontage_Implementation()
{
	PlayerAnimInst->ChangeAnimation(PostureValue);
	FPVPlayerAnimInst->ChangeAnimation(PostureValue);
}

void ATestCharacter::ChangeState_Implementation(EPlayerState _Type)
{
	StateValue = _Type;
}

void ATestCharacter::ChangePosture_Implementation(EPlayerPosture _Type)	// => 메인캐릭터로 이전해야 함 (내용 수정됨)
{
	if (_Type == EPlayerPosture::Barehand)
	{
		PostureValue = _Type;
		CurItemIndex = -1;

		// 아이템 메시 visibility 끄기
		ItemSocketMesh->SetVisibility(false);
		FPVItemSocketMesh->SetVisibility(false);
	}
	else
	{
		int ItemSlotIndex = static_cast<int>(_Type);
		if (IsItemIn[ItemSlotIndex] == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The item slot is empty."));
			return;
		}
		PostureValue = _Type;
		CurItemIndex = ItemSlotIndex;

		// 아이템 static mesh 세팅
		ItemSocketMesh->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);
		FPVItemSocketMesh->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);

		// 아이템 메시 transform 세팅
		ItemSocketMesh->SetRelativeLocation(ItemSlot[CurItemIndex].RelLoc);		
		FPVItemSocketMesh->SetRelativeLocation(ItemSlot[CurItemIndex].RelLoc);	

		ItemSocketMesh->SetRelativeRotation(ItemSlot[CurItemIndex].RelRot);		
		FPVItemSocketMesh->SetRelativeRotation(ItemSlot[CurItemIndex].RelRot);

		ItemSocketMesh->SetRelativeScale3D(ItemSlot[CurItemIndex].RelScale);
		FPVItemSocketMesh->SetRelativeScale3D(ItemSlot[CurItemIndex].RelScale);

		// 아이템 메시 visibility 켜기
		ItemSocketMesh->SetVisibility(true);
		FPVItemSocketMesh->SetVisibility(true);
	}
}

void ATestCharacter::ChangeLowerState_Implementation(EPlayerLowerState _LowerState)
{
	LowerStateValue = _LowerState;
}

void ATestCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir)
{
	DirValue = _Dir;
}

void ATestCharacter::PickUpItem_Implementation()	// => 메인캐릭터로 이전해야 함 (24.07.23 수정됨)
{
	// RayCast를 통해 Tag 이름을 가져온다.
	FString GetItemName = "";
	GetItemName = RayCastToItemName;

	// 맵에 아이템이 없을 경우.
	if (nullptr == GetMapItemData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("There is no item."));
		return;
	}

	// 1. 맵오브젝트일 경우
	AMapObjectBase* GetMapItem = Cast<AMapObjectBase>(GetMapItemData);
	if (nullptr != GetMapItem)
	{
		GetMapItem->InterAction();

		ABomb* GetSampleData = Cast<ABomb>(GetMapItem);
		if (nullptr != GetSampleData)
		{
			for (size_t i = 0; i < GetSampleData->Tags.Num(); i++)
			{
				FName GetItemTag = GetSampleData->Tags[i];
				if ("Sample" == GetItemTag)
				{
					GetSampleData->CharacterToDestroy();
				}
			}
		}

		return;
	}

	// 2. 주울 수 있는 아이템일 경우

	// 아이템의 Tag 이름을 통해 FName을 가져온다.
	FString TagName = "";
	for (size_t i = 0; i < GetMapItemData->Tags.Num(); i++)
	{
		TagName = GetMapItemData->Tags[i].ToString();
	}
	FName ItemStringToName = FName(*TagName);			// 아이템 이름

	// Data Table에서 아이템 검색하기.
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(ItemStringToName);

	EPlayerPosture ItemType = ItemData->GetType();		// 아이템 타입

	// 이미 인벤토리에 같은 이름을 가진 아이템이 있을 경우.
	if (ItemStringToName == ItemSlot[static_cast<int>(ItemType)].Name)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("The same item is already in inventory."));
		return;
	}

	// 이미 인벤토리에 같은 타입의 아이템이 있을 경우. (추후 수정될 수도 있음)
	if (true == IsItemIn[static_cast<uint8>(ItemType)])
	{
		CharacterPlayerToDropItem();
	}

	// Data Table에 있는 아이템 정보 가져오기.
	int ItemReloadNum = ItemData->GetReloadNum();		// 무기 장전 단위 (30, 40)	// -1일 경우 총기류 무기가 아님
	int ItemDamage = ItemData->GetDamage();				// 무기 공격력				// 0일 경우 무기가 아님
	UStaticMesh* ItemMeshRes = ItemData->GetResMesh();	// 스태틱 메시 리소스
	FVector ItemRelLoc = ItemData->GetRelLoc();			// 스태틱 메시 컴포넌트 상대적 위치
	FRotator ItemRelRot = ItemData->GetRelRot();		// 스태틱 메시 컴포넌트 상대적 회전
	FVector ItemRelScale = ItemData->GetRelScale();		// 스태틱 메시 컴포넌트 상대적 크기

	// 인벤토리에 아이템 집어넣기. (스태틱메시로 아이템을 가져가는 방식 채택!!!)
	uint8 ItemIndex = static_cast<uint8>(ItemType);		// 아이템을 넣을 인벤토리 인덱스
	IsItemIn[ItemIndex] = true;

	ItemSlot[ItemIndex].Name = ItemStringToName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	ItemSlot[ItemIndex].Damage = ItemDamage;
	ItemSlot[ItemIndex].MeshRes = ItemMeshRes;
	ItemSlot[ItemIndex].RelLoc = ItemRelLoc;
	ItemSlot[ItemIndex].RelRot= ItemRelRot;
	ItemSlot[ItemIndex].RelScale = ItemRelScale;

	// Map에 있는 아이템 삭제.
	GetMapItemData->Destroy();

	// 무기 Type에 따른 애니메이션 변화 함수 호출.
	ChangePosture(ItemType);
}

void ATestCharacter::ChangePOV()	// => 메인캐릭터로 이전해야 함 (24.07.22 수정됨)
{
	if (IsFPV)	// 일인칭 -> 삼인칭
	{
		// SpringArm Component
		SpringArmComponent->TargetArmLength = 300.0f;
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 60.0f, 110.0f));

		// Character Mesh
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);

		// Item Mesh
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(false);
			FPVItemSocketMesh->SetOwnerNoSee(true);
		}

		IsFPV = false;
	}
	else	// 삼인칭 -> 일인칭
	{
		// SpringArm Component
		SpringArmComponent->TargetArmLength = 0.0f;
		SpringArmComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 67.0f));

		// Character Mesh
		GetMesh()->SetOwnerNoSee(true);
		FPVMesh->SetOwnerNoSee(false);

		// Item Mesh
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(true);
			FPVItemSocketMesh->SetOwnerNoSee(false);
		}

		IsFPV = true;
	}
}

void ATestCharacter::CharacterReload()
{
	ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
}

void ATestCharacter::MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	GetMapItemData = _OtherActor;
}

void ATestCharacter::MapItemOverlapEnd()
{
	if (nullptr != GetMapItemData)
	{
		GetMapItemData = nullptr;
	}
}

void ATestCharacter::CrouchCameraMove()
{
	if (IsFPV)
	{
		switch (LowerStateValue)
		{
		case EPlayerLowerState::Idle:
			SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
			break;
		case EPlayerLowerState::Crouch:
			SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
			break;
		default:
			break;
		}
	}
}

void ATestCharacter::NetCheck()
{
	IsServer = GetWorld()->GetAuthGameMode() != nullptr;
	IsClient = !IsServer;

	if (true == IsServer)
	{
		IsCanControlled = (GetLocalRole() == ROLE_Authority) ? true : false;
	}
	else // client
	{
		IsCanControlled = (GetLocalRole() == ROLE_AutonomousProxy) ? true : false;
	}

	if (true == IsServer)
	{
		UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
		// 이토큰은 그 인덱스가 아니다.
		Token = Inst->GetNetToken();
		MyMaxHp = Inst->GetPlayerData(FName("TestPlayer"))->GetHp();

		// UGameplayStatics::GetPlayerPawn(Token)
	}
	else // client
	{

	}
}

void ATestCharacter::SendTokenToHpBarWidget()
{
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	if (nullptr == Con)
	{
		return;
	}
	ATestPlayHUD* PlayHUD = Cast<ATestPlayHUD>(Con->GetHUD());
	if (nullptr == PlayHUD)
	{
		return;
	}
	UTestHpBarUserWidget* MyHpWidget = Cast<UTestHpBarUserWidget>(PlayHUD->GetWidget(EUserWidgetType::HpBar));
	if (nullptr == MyHpWidget)
	{
		return;
	}

	if (true == IsCanControlled && -1 != Token)
	{
		MyHpWidget->HpbarInit_ForMainPlayer(Token);
	}
	else
	{
		int a = 0;
		return;
	}
}

void ATestCharacter::UpdatePlayerHp(float _DeltaTime)
{
	ATestPlayerState* MyTestPlayerState = GetPlayerState<ATestPlayerState>();
	if (nullptr == MyTestPlayerState)
	{
		return;
	}

	ATestPlayerController* MyController = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (nullptr == MyController)
	{
		return;
	}


	float GetHp = MyTestPlayerState->GetPlayerHp();

	if (CurHp != GetHp || /*test*/MyMaxHp != PlayerHp)
	{		
		
		CurHp = MyTestPlayerState->GetPlayerHp();

		ATestPlayHUD* PlayHUD = Cast<ATestPlayHUD>(MyController->GetHUD());
		if (nullptr != PlayHUD && Token != -1)
		{
			UTestHpBarUserWidget* MyHpWidget = Cast<UTestHpBarUserWidget>(PlayHUD->GetWidget(EUserWidgetType::HpBar));
			MyHpWidget->NickNameUpdate(Token, FText::FromString(FString("CORORO")));
			MyHpWidget->HpbarUpdate(Token, CurHp, 100.0f);
		}
	}
}