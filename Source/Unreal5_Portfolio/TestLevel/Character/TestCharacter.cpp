// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/SphereComponent.h"
#include "TestPlayerController.h"
#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "PartDevLevel/Character/PlayerAnimInstance.h"

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
	GetMesh()->bHiddenInSceneCapture = true;
	GetMesh()->SetOwnerNoSee(true);

	// FPV Character Mesh
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// Item Mesh => 메인캐릭터로 이전해야 함 (새로 추가됨)
	ItemSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSocket"));
	ItemSocket->SetupAttachment(GetMesh(), "ItemSocket");
	ItemSocket->SetCollisionProfileName(TEXT("NoCollision"));
	ItemSocket->SetGenerateOverlapEvents(true);
	ItemSocket->SetOwnerNoSee(true);
	ItemSocket->SetVisibility(false);
	ItemSocket->SetIsReplicated(true);

	// FPV Item Mesh => 메인캐릭터로 이전해야 함 (새로 추가됨)
	FPVItemSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FPVItemSocket"));
	FPVItemSocket->SetupAttachment(FPVMesh, "FPVItemSocket");
	FPVItemSocket->SetCollisionProfileName(TEXT("NoCollision"));
	FPVItemSocket->SetGenerateOverlapEvents(true);
	FPVItemSocket->SetOnlyOwnerSee(true);
	FPVItemSocket->bCastDynamicShadow = false;
	FPVItemSocket->CastShadow = false;
	FPVItemSocket->SetVisibility(false);
	FPVItemSocket->SetIsReplicated(true);


	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		/*
		// Weapon Meshes
		FString Name = Enum->GetNameStringByValue(i) + "Socket";
		UStaticMeshComponent* NewSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSocketMesh->SetupAttachment(GetMesh(), *Name);
		NewSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewSocketMesh->SetGenerateOverlapEvents(true);
		NewSocketMesh->SetVisibility(false);
		NewSocketMesh->SetIsReplicated(true);
		ItemMeshes.Push(NewSocketMesh);
		*/

		// Inventory (for UI Test)
		FItemInformation NewSlot;
		NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;
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

void ATestCharacter::CharacterPlayerToDropItem_Implementation(FName _ItemName, FTransform _Transform)
{
	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	//const FItemDataRow* ItemBase = MainGameInst->GetItemData(_ItemName);
	//GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), _Transform);


	const FItemDataRow* ItemBase = MainGameInst->GetItemData(FName("TestRifle"));

	GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), _Transform);
}

void ATestCharacter::Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
	if (nullptr == Monster)
	{
		return;
	}
}

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
	Super::BeginPlay();
	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	// 몽타주 변경에 필요한 세팅 추가 필요 (태환)
	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DefaultRayCast(DeltaTime);

	TArray<FItemInformation> I = ItemSlot;
	AGameModeBase* Ptr = GetWorld()->GetAuthGameMode();
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
}

void ATestCharacter::TestRayCast(float _DeltaTime, FVector _StartPos, FVector _EndPos, FRotator _CameraRot)
{
	FVector Start = GetActorLocation();
	Start.X += _StartPos.X;
	Start.Y += _StartPos.Y;
	Start.Z += _StartPos.Z;

	CameraComponent->AddLocalRotation(_CameraRot);
	FVector ForwardVector = CameraComponent->GetForwardVector();

	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));

	FVector End = Start + (ForwardVector * 1000);

	FHitResult Hit;
	if (GetWorld())
	{
		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, FCollisionQueryParams(), FCollisionResponseParams());
		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0.0f, 0.0f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, _DeltaTime, 0.0f, 0.0f);

		if (true == ActorHit && Hit.GetActor())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, Hit.GetActor()->GetFName().ToString());
			//Hit.GetActor()->ActorHasTag(TEXT(""));
			//AActor* GetActorTest = Hit.GetActor();
			GetMapItem = Hit.GetActor();
			int TagCount = Hit.GetActor()->Tags.Num();
			if (0 != TagCount)
			{
				for (size_t i = 0; i < Hit.GetActor()->Tags.Num(); i++)
				{
					FString TagName = Hit.GetActor()->Tags[i].ToString();
					RayCastToItemName = TagName;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TagName);
				}
			}
		}
		else
		{
			GetMapItem = nullptr;
			RayCastToItemName = "";
		}
	}
}

void ATestCharacter::DefaultRayCast(float _DeltaTime)
{
	FVector Start = GetActorLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));
	FVector End = Start + (ForwardVector * 1000);

	// 아이템 줍기.
	FHitResult Hit;
	if (GetWorld())
	{
		// 아이템 콜리전 충돌.
		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, FCollisionQueryParams(), FCollisionResponseParams());
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, _DeltaTime, 0.0f, 0.0f);

		if (true == ActorHit && Hit.GetActor())
		{
			GetMapItem = Hit.GetActor();
			int TagCount = Hit.GetActor()->Tags.Num();
			if (0 != TagCount)
			{
				for (size_t i = 0; i < Hit.GetActor()->Tags.Num(); i++)
				{
					FString TagName = Hit.GetActor()->Tags[i].ToString();
					RayCastToItemName = TagName;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TagName);
				}
			}
		}
		else
		{
			GetMapItem = nullptr;
			RayCastToItemName = "";
		}
	}
}

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

		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel9, FCollisionQueryParams(), FCollisionResponseParams());
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, _DeltaTime, 0.0f, 0.0f);

		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			FString BoneName = Hit.BoneName.ToString();
			UE_LOG(LogTemp, Warning, TEXT("Bone Name : %s"), *BoneName);
			ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Hit.GetActor());
			if (nullptr != Monster)
			{
				Monster->Damaged(50.0f);
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : -50"), *Monster->GetName()));
			}
		}
	}
}

//void ATestCharacter::ChangeMontage_Implementation()
//{
//	PlayerAnimInst->ChangeAnimation(PostureValue);
//	ClientChangeMontage();
//}
//
//void ATestCharacter::ClientChangeMontage_Implementation()
//{
//	PlayerAnimInst->ChangeAnimation(PostureValue);
//}

void ATestCharacter::ChangeState_Implementation(EPlayerState _Type)
{
	StateValue = _Type;
}

void ATestCharacter::ChangePosture_Implementation(EPlayerPosture _Type)
{
	if (_Type == EPlayerPosture::Barehand)
	{
		PostureValue = _Type;
		CurItemIndex = -1;

		// 아이템 메시 visibility 끄기
		ItemSocket->SetVisibility(false);
		FPVItemSocket->SetVisibility(false);
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
		ItemSocket->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);
		FPVItemSocket->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);

		/* 아이템 메시 transform 세팅 */

		// 아이템 메시 visibility 켜기
		ItemSocket->SetVisibility(true);
		FPVItemSocket->SetVisibility(true);
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

void ATestCharacter::PickUpItem_Implementation()	// => 메인캐릭터로 이전해야 함 (내용 수정됨)
{
	//AGameModeBase* Test = GetWorld()->GetAuthGameMode();
	//ATestPlayerController* PlayerControl = Cast<ATestPlayerController>(GetController());
	
	// RayCast를 통해 Tag 이름을 가져온다.
	FString GetItemName = "";
	GetItemName = RayCastToItemName;

	if (GetItemName == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Not Item"));
		return;
	}

	FName ItemStringToName = FName(*GetItemName);

	// Data Table에 있는 Static Mesh 가져오기.
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(ItemStringToName);

	EPlayerPosture ItemType = ItemData->GetType();	// 무기 Type
	UStaticMesh* ItemMeshRes = ItemData->GetResMesh(); // Static Mesh
	int ItemReloadNum = ItemData->GetReloadNum();	// 장전 단위.(30, 40)

	uint8 ItemIndex = static_cast<uint8>(ItemType); // 사용할 인벤토리 인덱스

	// 인벤토리에 아이템 집어넣기. (스태틱메시로 아이템을 가져가는 방식 채택!!!)
	ItemSlot[ItemIndex].Name = ItemStringToName;
	ItemSlot[ItemIndex].MeshRes = ItemMeshRes;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	IsItemIn[ItemIndex] = true;

	// Map에 있는 아이템 삭제.
	GetMapItem->Destroy(); 

	// 무기 Type에 따른 애니메이션 변화 함수 호출.
	ChangePosture(ItemType);
}

void ATestCharacter::ChangePOV()	// => 메인캐릭터로 이전해야 함 (내용 수정됨)
{
	if (IsFPV)
	{
		// SpringArm Component
		SpringArmComponent->TargetArmLength = 200.0f;
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

		// Character Mesh
		GetMesh()->SetOnlyOwnerSee(true);
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);
		FPVMesh->SetOnlyOwnerSee(false);

		// Item Meshes
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocket->SetOnlyOwnerSee(true);
			ItemSocket->SetOwnerNoSee(false);
			FPVItemSocket->SetOwnerNoSee(true);
			FPVItemSocket->SetOnlyOwnerSee(false);
		}

		IsFPV = false;
	}
	else
	{
		// SpringArm Component
		SpringArmComponent->TargetArmLength = 0.0f;
		SpringArmComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 67.0f));

		// Character Mesh
		GetMesh()->SetOwnerNoSee(true);
		GetMesh()->SetOnlyOwnerSee(false);
		FPVMesh->SetOnlyOwnerSee(true);
		FPVMesh->SetOwnerNoSee(false);

		// Item Meshes
		for (int i = 0; i < int(EPlayerPosture::Barehand); i++)
		{
			ItemSocket->SetOwnerNoSee(true);
			ItemSocket->SetOnlyOwnerSee(false);
			FPVItemSocket->SetOnlyOwnerSee(true);
			FPVItemSocket->SetOwnerNoSee(false);
		}

		IsFPV = true;
	}
}