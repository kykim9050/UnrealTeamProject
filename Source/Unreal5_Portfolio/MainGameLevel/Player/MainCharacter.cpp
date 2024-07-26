// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainCharacter.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MainPlayerController.h"
#include "PlayerItemInformation.h"
#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "Components/SphereComponent.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "MainGameLevel/Object/Bomb.h"
#include "MainGameLevel/UI/Title/MainTitleHUD.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init

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
	//MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	//MinimapIconComponent->SetupAttachment(RootComponent);
	//MinimapIconComponent->bVisibleInSceneCaptureOnly = true;
	
	// character Mesh
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bHiddenInSceneCapture = true;

	// FPV Character Mesh
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// Riding Character Mesh
	//RidingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RidingMesh"));
	//RidingMesh->SetupAttachment(GetMesh());
	//RidingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	//RidingMesh->SetVisibility(false);
	//RidingMesh->SetIsReplicated(true);
	//RidingMesh->bHiddenInSceneCapture = true;

	// 아이템 장착 소켓 초기화.
	ItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSocketMesh"));
	ItemSocketMesh->SetupAttachment(GetMesh(), FName("ItemSocket"));
	ItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ItemSocketMesh->SetGenerateOverlapEvents(true);
	ItemSocketMesh->SetOwnerNoSee(true);
	ItemSocketMesh->SetVisibility(false);
	ItemSocketMesh->SetIsReplicated(true);
	ItemSocketMesh->bHiddenInSceneCapture = true;

	// 1인칭 아이템 장착 소켓 초기화.
	FPVItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FPVItemSocketMesh"));
	FPVItemSocketMesh->SetupAttachment(FPVMesh, FName("FPVItemSocket"));
	FPVItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	FPVItemSocketMesh->SetGenerateOverlapEvents(true);
	FPVItemSocketMesh->SetOnlyOwnerSee(true);
	FPVItemSocketMesh->SetVisibility(false);
	FPVItemSocketMesh->SetIsReplicated(true);
	FPVItemSocketMesh->bCastDynamicShadow = false;
	FPVItemSocketMesh->CastShadow = false;

	// Item Create Component
	CreateItemComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CreateItemComponent"));
	CreateItemComponent->SetupAttachment(RootComponent);
	CreateItemComponent->SetRelativeLocation(FVector(100.0, 0.0, -90.0));

	// Map Item 
	GetMapItemCollisonComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("GetMapItemCollisionComponent"));
	GetMapItemCollisonComponent->SetupAttachment(RootComponent);
	GetMapItemCollisonComponent->SetRelativeLocation(FVector(60.0, 0.0, -5.0f));
	GetMapItemCollisonComponent->SetCollisionProfileName(FName("MapItemSearch"));
	GetMapItemCollisonComponent->SetBoxExtent(FVector(40.0, 50.0, 80.0));

	// Inventory
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		FPlayerItemInformation SlotBase;
		SlotBase.Name = "";
		SlotBase.ReloadMaxNum = -1;
		SlotBase.ReloadLeftNum = -1;
		ItemSlot.Push(SlotBase);
		IsItemIn.Push(false);
	}

	// Hand Attack Component
	HandAttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hand Attack Comp"));
	HandAttackComponent->SetupAttachment(GetMesh());
	HandAttackComponent->SetRelativeLocation({ 0.0f, 100.0f, 110.0f });
}

void AMainCharacter::PostInitializeComponents() // FName 부분 수정 필요.
{
	if (GetWorld()->WorldType == EWorldType::Game
		|| GetWorld()->WorldType == EWorldType::PIE)
	{
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		if (nullptr == MainGameInst)
		{
			return;
		}

		// 스켈레탈 메쉬 선택
		USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("AlienSoldier"))->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);

		// ABP 선택
		UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("AlienSoldier"))->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}

	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	NetCheck();
	Super::BeginPlay();
	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	FPVPlayerAnimInst = Cast<UPlayerAnimInstance>(FPVMesh->GetAnimInstance());

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 하체 정보
	DOREPLIFETIME(AMainCharacter, LowerStateValue);
	// 플레이어 자세 유형.
	DOREPLIFETIME(AMainCharacter, PostureValue);
	DOREPLIFETIME(AMainCharacter, DirValue);

	DOREPLIFETIME(AMainCharacter, Token);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerHp(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::ChangePosture_Implementation(EPlayerPosture _Type)
{
	// Bomb, Drink 상태인 경우 자세를 변경할 수 없도록 수정.
	if (_Type == EPlayerPosture::Bomb || _Type == EPlayerPosture::Drink)
	{
		return;
	}
	else if (_Type == EPlayerPosture::Barehand) // 맨손 자세로 변경.
	{
		PostureValue = _Type;
		CurItemIndex = -1;

		ItemSocketMesh->SetVisibility(false);
		FPVItemSocketMesh->SetVisibility(false);
	}
	else // 무기를 든 자세로 변경.
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

void AMainCharacter::ChangeLowerState_Implementation(EPlayerLowerState _LowerState)
{
	LowerStateValue = _LowerState;
}

void AMainCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir)
{
	DirValue = _Dir;
}

void AMainCharacter::PickUpItem_Implementation()
{
	// 맵에 아이템이 없을 경우. -> 콜리전에 충돌이 없는 경우
	if (nullptr == GetMapItemData)
	{
		return;
	}

	// 1. 맵오브젝트일 경우
	{
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
	}

	// 2. 주울 수 있는 아이템일 경우
	// 맵에 Actor가 있다면 해당 Actor의 Tag를 가져온다.
	FString TagName = "";
	for (size_t i = 0; i < GetMapItemData->Tags.Num(); i++) // 불안한 곳.
	{
		TagName = GetMapItemData->Tags[i].ToString();
	}

	FName ItemStringToName = FName(*TagName);

	// ItemName에 맞는 아이템 정보를 DT에서 가져온다.
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(ItemStringToName);

	EPlayerPosture ItemType = ItemData->GetType();		// 아이템 타입

	// 이미 인벤토리에 같은 이름을 가진 아이템이 있을 경우.
	if (ItemStringToName == ItemSlot[static_cast<int>(ItemType)].Name)
	{
		return;
	}

	// 이미 인벤토리에 같은 타입의 아이템이 있을 경우. (추후 수정될 수도 있음)
	if (true == IsItemIn[static_cast<uint8>(ItemType)])
	{
		CharacterPlayerToDropItem();
	}

	int ItemReloadNum = ItemData->GetReloadNum();		// 무기 장전 단위 (30, 40)	// -1일 경우 총기류 무기가 아님
	int ItemDamage = ItemData->GetDamage();				// 무기 공격력				// 0일 경우 무기가 아님
	UStaticMesh* ItemMeshRes = ItemData->GetResMesh();	// 스태틱 메시
	FVector ItemRelLoc = ItemData->GetRelLoc();			// 스태틱 메시 컴포넌트 상대적 위치
	FRotator ItemRelRot = ItemData->GetRelRot();		// 스태틱 메시 컴포넌트 상대적 회전
	FVector ItemRelScale = ItemData->GetRelScale();		// 스태틱 메시 컴포넌트 상대적 크기

	uint8 ItemIndex = static_cast<uint8>(ItemType);		// 아이템을 넣을 인벤토리 인덱스

	// 손에 아이템을 생성한다.
	// 인벤토리에 아이템 집어넣기. (스태틱메시로 아이템을 가져가는 방식 채택!!!)
	IsItemIn[ItemIndex] = true;

	ItemSlot[ItemIndex].Name = ItemStringToName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	ItemSlot[ItemIndex].Damage = ItemDamage;
	ItemSlot[ItemIndex].MeshRes = ItemMeshRes;
	ItemSlot[ItemIndex].RelLoc = ItemRelLoc;
	ItemSlot[ItemIndex].RelRot = ItemRelRot;
	ItemSlot[ItemIndex].RelScale = ItemRelScale;

	// 주은 무기 삭제.
	GetMapItemData->Destroy();

	// 무기 Type에 따른 애니메이션 변화 함수 호출.
	ChangePosture(ItemType);
}

void AMainCharacter::CharacterPlayerToDropItem_Implementation()
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
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	const FItemDataRow* ItemBase = MainGameInst->GetItemData(ItemName);
	FTransform BoneTrans = GetMesh()->GetBoneTransform(FName("weapon_r"), ERelativeTransformSpace::RTS_World);
	GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), BoneTrans);

	// 손에 들고 있던 아이템을 인벤토리에서 삭제
	FPlayerItemInformation NewSlot;
	ItemSlot[CurItemIndex] = NewSlot;
	IsItemIn[CurItemIndex] = false;

	// 자세를 맨손으로 변경
	ChangePosture(EPlayerPosture::Barehand);
}

void AMainCharacter::FireRayCast_Implementation(float _DeltaTime)
{
	if (CurItemIndex == -1 || CurItemIndex == 2 || CurItemIndex == 5)
	{
		// 주먹, 근거리
		if (PostureValue == EPlayerPosture::Barehand || PostureValue == EPlayerPosture::Melee)
		{
			ChangeMontage();
		}
		return;
	}

	// 탄알이 없다면 
	if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	{
		//ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
		// 장전하라는 Widget을 띄워야 함.
		// 장전 함수는 CharacterReload 이다.
		return;
	}

	


	AMainPlayerController* Con = Cast<AMainPlayerController>(GetController());
	FVector Start = GetMesh()->GetSocketLocation(FName("weapon_r_muzzle"));
	Start.Z -= 20.0f;
	FVector End = (Con->GetControlRotation().Vector() * 2000.0f) + Start;
	
	FHitResult Hit;
	if (GetWorld())
	{
		// 탄수 깎기.
		ItemSlot[CurItemIndex].ReloadLeftNum -= 1;

		// Ray Cast
		TArray<AActor*> IgnoreActors; // 무시할 Actor들.
		bool ActorHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		
		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			FString BoneName = Hit.BoneName.ToString();
			//UE_LOG(LogTemp, Warning, TEXT("Bone Name : %s"), *BoneName);
			ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(Hit.GetActor());
			if (nullptr != Monster)
			{
				Monster->Damaged(ItemSlot[CurItemIndex].Damage);
			}
		}
	}
}

void AMainCharacter::ChangeMontage_Implementation()
{
	PlayerAnimInst->ChangeAnimation(PostureValue);
	FPVPlayerAnimInst->ChangeAnimation(PostureValue);

	ClientChangeMontage();
}

void AMainCharacter::ClientChangeMontage_Implementation()
{
	PlayerAnimInst->ChangeAnimation(PostureValue);
	FPVPlayerAnimInst->ChangeAnimation(PostureValue);
}

void AMainCharacter::CrouchCameraMove()
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

void AMainCharacter::MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	GetMapItemData = _OtherActor;
}

void AMainCharacter::MapItemOverlapEnd()
{
	if (nullptr != GetMapItemData)
	{
		GetMapItemData = nullptr;
	}
}

void AMainCharacter::UpdatePlayerHp(float _DeltaTime)
{
	AMainPlayerState* MyMainPlayerState = GetPlayerState<AMainPlayerState>();
	if (nullptr == MyMainPlayerState)
	{
		return;
	}

	AMainPlayerController* MyController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (nullptr == MyController)
	{
		return;
	}

	float GetHp = MyMainPlayerState->GetPlayerHp();

	// Get HUD
	// AMainPlayHUD PlayHUD = Cast<AMainPlayHUD>(MyController->GetHUD());
	// if(nullptr == )
	// {
	//     UHpBarUserWidget* MyHpWidget = Cast<UHpBarUserWidget>(PlayHUD->GetWidget(EInGameUIType::HpBar));
	//     MyHpWidget->NickNameUpdate(Token, FText::FromString(FString("")));
	//     MyHpWidget->HpbarUpdate(Token, CurHp, 100.0f);
	// {
}

void AMainCharacter::ChangePOV()
{
	if (IsFPV)
	{
		// SpringArm 위치 수정
		SpringArmComponent->TargetArmLength = 200.0f;
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

		// Character Mesh 전환
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);

		// Item Mesh
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(false);
			FPVItemSocketMesh->SetOwnerNoSee(true);
		}

		// 일인칭 -> 삼인칭
		IsFPV = false;
	}
	else
	{
		// SpringArm 위치 수정
		SpringArmComponent->TargetArmLength = 0.0f;
		SpringArmComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 67.0f));

		// Character Mesh 전환
		GetMesh()->SetOwnerNoSee(true);
		FPVMesh->SetOwnerNoSee(false);

		// Item Mesh
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(true);
			FPVItemSocketMesh->SetOwnerNoSee(false);
		}

		// 삼인칭 -> 일인칭
		IsFPV = true;
	}
}

void AMainCharacter::CharacterReload()
{
	if (-1 == CurItemIndex)
	{
		return;
	}
	ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
}

void AMainCharacter::HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	{
		ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(_OtherActor);
		if (nullptr != Monster)
		{
			Monster->Damaged(150.0f);
		}
	}

	{
		ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(_OtherActor); // 추후 Main으로 바꿔야 함.
		if (nullptr != BossMonster)
		{
			BossMonster->Damaged(150.0f);
		}
	}
}

void AMainCharacter::ChangeHandAttackCollisionProfile(FName _Name)
{
	HandAttackComponent->SetCollisionProfileName(_Name);
}

void AMainCharacter::NetCheck()
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
	}
}

void AMainCharacter::SendTokenToHpBarWidget()
{
	//AMainPlayerController* Con = Cast<AMainPlayerController>(GetController());
	//if (nullptr == Con)
	//{
	//	return;
	//}
	//AMainPlayHUD* PlayHUD = Cast<ATestPlayHUD>(Con->GetHUD());
	//if (nullptr == PlayHUD)
	//{
	//	return;
	//}
	//UTestHpBarUserWidget* MyHpWidget = Cast<UTestHpBarUserWidget>(PlayHUD->GetWidget(EUserWidgetType::HpBar));
	//if (nullptr == MyHpWidget)
	//{
	//	return;
	//}

	//if (true == IsCanControlled && -1 != Token)
	//{
	//	MyHpWidget->HpbarInit_ForMainPlayer(Token);
	//}
}

TArray<struct FPlayerItemInformation> AMainCharacter::GetItemSlot()
{
	return ItemSlot;
}
