// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "TestLevel/UI/TestPlayHUD.h"
#include "TestLevel/UI/TestHpBarUserWidget.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "TestLevel/Item/WeaponBase.h"
#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"
#include "PartDevLevel/Object/TestArea.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "MainGameLevel/Object/Bomb.h"
#include "MainGameLevel/Object/DoorObject.h"
#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"
#include "TestPlayerController.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ATestCharacter::ATestCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character Mesh => 메인캐릭터 이전 필요 (24.07.29 수정됨) => 메인 적용.
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->bHiddenInSceneCapture = true;

	// Item Mesh => 메인캐릭터 적용.
	ItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSocketMesh"));
	ItemSocketMesh->SetupAttachment(GetMesh(), FName("ItemSocket"));
	ItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ItemSocketMesh->SetGenerateOverlapEvents(true);
	ItemSocketMesh->SetOwnerNoSee(true);
	ItemSocketMesh->SetVisibility(false);
	ItemSocketMesh->SetIsReplicated(true);
	ItemSocketMesh->bHiddenInSceneCapture = true;

	// SpringArm Component => 메인캐릭터 이전 필요 (24.07.29 수정됨)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc);
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = true;

	// Camera Component => 메인캐릭터 이전 필요 (24.07.29 수정됨)
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	// FPV Character Mesh => 메인캐릭터 이전 필요 (24.07.29 수정됨)
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -160.0f));
	FPVMesh->SetOwnerNoSee(false);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// FPV Item Mesh => 메인캐릭터 적용.
	FPVItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FPVItemSocketMesh"));
	FPVItemSocketMesh->SetupAttachment(FPVMesh, FName("FPVItemSocket"));
	FPVItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	FPVItemSocketMesh->SetGenerateOverlapEvents(true);
	FPVItemSocketMesh->SetOnlyOwnerSee(true);
	FPVItemSocketMesh->SetVisibility(false);
	FPVItemSocketMesh->SetIsReplicated(true);
	FPVItemSocketMesh->bCastDynamicShadow = false;
	FPVItemSocketMesh->CastShadow = false;

	// Map Item 검사 => 메인캐릭터 적용.
	GetMapItemCollisonComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("GetMapItemCollisionComponent"));
	GetMapItemCollisonComponent->SetupAttachment(RootComponent);
	GetMapItemCollisonComponent->SetRelativeLocation(FVector(100.0, 0.0, -20.0f));
	GetMapItemCollisonComponent->SetCollisionProfileName(FName("MapItemSearch"));

	UEnum* Enum = StaticEnum<EPlayerPosture>();

	// = > 메인캐릭터 적용. [주석 부분 다르니 확인 요청.]
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

	// HandAttack Component => 메인캐릭터 적용.[주석이 없는 3줄 적용. 확인 필요.]
	//FString Name = "Punch";
	HandAttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hand Attack Comp"));
	HandAttackComponent->SetupAttachment(GetMesh());
	HandAttackComponent->SetRelativeLocation({ 0.0f, 100.0f, 120.0f });

	// MinimapIcon Component => 메인캐릭터 적용.
	MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	MinimapIconComponent->SetupAttachment(RootComponent);
	MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// HeadName Component	// => 메인으로 이전 필요 (24.07.30 추가됨)
	HeadNameComponent = CreateDefaultSubobject<UHeadNameWidgetComponent>(TEXT("HeadNameWidgetComponent"));
	HeadNameComponent->SetupAttachment(RootComponent);
	HeadNameComponent->SetOwnerNoSee(true);
	HeadNameComponent->bHiddenInSceneCapture = true;

	// Riding Character Mesh => 메인캐릭터 적용.(주석)
	RidingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RidingMesh"));
	RidingMesh->SetupAttachment(GetMesh());
	RidingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	RidingMesh->SetVisibility(false);
	RidingMesh->SetIsReplicated(true);
	RidingMesh->bHiddenInSceneCapture = true;

	MuzzleParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleParticle"));
	MuzzleParticleComponent->SetupAttachment(RootComponent);
	MuzzleParticleComponent->SetIsReplicated(true);
	MuzzleParticleComponent->SetVisibility(false);
}

//void ATestCharacter::Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
//{
//	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
//	if (nullptr == Monster)
//	{
//		return;
//	}
//}

void ATestCharacter::HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision) // => 매인 캐릭터에 적용.
{
	{
		ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
		if (nullptr != Monster)
		{
			Monster->Damaged(150.0f);
		}
	}

	{
		ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(_OtherActor);
		if (nullptr != BossMonster)
		{
			BossMonster->Damaged(150.0f);
		}
	}
}

void ATestCharacter::ChangeHandAttackCollisionProfile(FName _Name) // => 매인 적용.
{
	HandAttackComponent->SetCollisionProfileName(_Name);
}

// 메인 플레이어 추가 필요 코드 (태환) 07/24 => 매인 적용.
void ATestCharacter::PostInitializeComponents()
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
		USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("Vanguard"))->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);

		// 팔 메쉬 선택 (메인 추가 필요)
		USkeletalMesh* FPVSkeletalMesh = MainGameInst->GetPlayerData(FName("Vanguard"))->GetPlayerFPVPlayerSkeletalMesh();
		FPVMesh->SetSkeletalMesh(FPVSkeletalMesh);

		// ABP 선택
		UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("Vanguard"))->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}

	Super::PostInitializeComponents();

}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	NetCheck();
	Super::BeginPlay();

	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	// 몽타주 변경에 필요한 세팅 추가 필요 (태환) // => 매인 적용.
	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	FPVPlayerAnimInst = Cast<UPlayerAnimInstance>(FPVMesh->GetAnimInstance());

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
	//UISetting();

	SettingPlayerState();
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerHp(DeltaTime); // => 매인 적용.

	// 다른 플레이어의 HeadNameComponent가 항상 나를 향하도록 회전	// => 메인 이전 필요 (24.07.30 추가됨)
	if (nullptr != HeadNameComponent)
	{
		HeadNameComponent->BilboardRotate(GetActorLocation());
	}

	// 7/29 기절 상태일 때 캐릭터 회전 금지 코드
	if (IsFaint == false) // 정상 상태 
	{
		bUseControllerRotationYaw = true;
	}
	else // 기절 상태
	{
		bUseControllerRotationYaw = false;
	}

#if WITH_EDITOR
	// GameState 변수 출력용 TestCode
	{
		AMainGameState* CurGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

		if (nullptr == CurGameState)
		{
			return;
		}

		EGameStage StageNum = CurGameState->GetCurStage();
		FString StageString = FString();
		const UEnum* StateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameStage"), true);
		if (StateEnum)
		{
			StageString = StateEnum->GetNameStringByValue((int64)StageNum);
		}
		UMainGameBlueprintFunctionLibrary::DebugTextPrint(GetWorld(), FString(TEXT("CurStage = ")) + StageString);
	}
#endif
	//DefaultRayCast(DeltaTime);
	//TArray<FItemInformation> I = ItemSlot;
	//AGameModeBase* Ptr = GetWorld()->GetAuthGameMode();
}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// State, Posture, Action
	DOREPLIFETIME(ATestCharacter, StateValue);
	DOREPLIFETIME(ATestCharacter, PostureValue);	// => 매인 적용.
	DOREPLIFETIME(ATestCharacter, LowerStateValue); // => 매인 적용.
	DOREPLIFETIME(ATestCharacter, DirValue);		// => 매인 적용.
	DOREPLIFETIME(ATestCharacter, IsFaint);			// 7/26 추가
	DOREPLIFETIME(ATestCharacter, IsBombSetting);	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)

	// Item
	DOREPLIFETIME(ATestCharacter, RayCastToItemName);

	// Server?
	DOREPLIFETIME(ATestCharacter, Token); // => 매인 적용.
}

void ATestCharacter::FireRayCast_Implementation() // => 메인 수정 필요 (24.07.30 DebugMessage 부분 수정됨)
{
	if (CurItemIndex == -1 || CurItemIndex == 2)
	{
		return;
	}

	if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	{
		ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	}

	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	FVector Start = GetMesh()->GetSocketLocation(FName("MuzzleSocket"));
	//Start.Z -= 20.0f;
	FVector End = (Con->GetControlRotation().Vector() * 2000.0f) + Start;
	FHitResult Hit;

	if (GetWorld())
	{
		ItemSlot[CurItemIndex].ReloadLeftNum -= 1;
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Bullet left : %d / %d"), ItemSlot[CurItemIndex].ReloadLeftNum, ItemSlot[CurItemIndex].ReloadMaxNum));
#endif // WITH_EDITOR

		//bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel9, FCollisionQueryParams(), FCollisionResponseParams());
		TArray<AActor*> IgnoreActors;
		bool ActorHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0.0f, 0.0f);

		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			FString BoneName = Hit.BoneName.ToString();
			UE_LOG(LogTemp, Warning, TEXT("Bone Name : %s"), *BoneName);
			{
				ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Hit.GetActor()); // [Main] ABasicMonsterBase
				if (nullptr != Monster)
				{
					Monster->Damaged(ItemSlot[CurItemIndex].Damage);
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : %d"), *Monster->GetName(), ItemSlot[CurItemIndex].Damage));
				}
			}
			{
				ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(Hit.GetActor());
				if (nullptr != BossMonster)
				{
					BossMonster->Damaged(ItemSlot[CurItemIndex].Damage);
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : %d"), *BossMonster->GetName(), ItemSlot[CurItemIndex].Damage));
				}
			}
		}
	}
}

void ATestCharacter::Drink_Implementation()	// => 메인에 추후 이전해야 함 (24.07.31 수정 및 테스팅 중)
{
	// 음료 아이템이 없다면 return
	if (false == IsItemIn[3])
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), 4));
#endif // WITH_EDITOR
		return;
	}

	// 자세 변경
	ChangePosture(EPlayerPosture::Drink);

	// 실질적으로 플레이어 HP가 회복되는 부분
	ATestPlayerState* MyTestPlayerState = GetPlayerState<ATestPlayerState>();
	if (nullptr == MyTestPlayerState)
	{
		return;
	}
	MyTestPlayerState->HealHp();

#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("HP recovered!")));
#endif // WITH_EDITOR

	// 아이템 삭제
	DeleteItem(3);
}

void ATestCharacter::DrinkComplete_Implementation()	// => 메인에 추후 이전해야 함 (24.07.30 추가 후 테스팅 중)
{
	ChangePosture(static_cast<EPlayerPosture>(PrevItemIndex));
}

void ATestCharacter::BombSetStart_Implementation()	// => 메인에 추후 이전해야 함 (24.07.31 수정 및 테스팅 중)
{
	// 폭탄 아이템이 없다면 return
	if (false == IsItemIn[4])
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), 5));
#endif // WITH_EDITOR
		return;
	}

	// 폭탄 설치 가능한 Area가 아닐 경우 return
	ATestArea* AreaObject = Cast<ATestArea>(GetMapItemData);
	if (nullptr == AreaObject)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("You have to set the bomb in proper area.")));
#endif // WITH_EDITOR
		return;
	}

	// 폭탄 설치 가능한 것으로 판단, 설치 시작
	IsBombSetting = true;
#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString(TEXT("Bomb setting start.")));
#endif // WITH_EDITOR

	// 애니메이션 변경
	ChangePosture(EPlayerPosture::Bomb);
}

void ATestCharacter::BombSetTick_Implementation()		// => 메인에 추후 이전해야 함 (24.07.31 수정 및 테스팅 중)
{
	// 폭탄 설치 중일 경우만
	if (true == IsBombSetting)
	{
		AMapObjectBase* AreaObject = Cast<AMapObjectBase>(GetMapItemData);
		if (nullptr != AreaObject)
		{
			AreaObject->InterAction();
		}
	}
}

void ATestCharacter::BombSetCancel_Implementation()		// => 메인에 추후 이전해야 함 (24.07.31 수정 및 테스팅 중)
{
	// 폭탄 설치 중일 경우만
	if (true == IsBombSetting)
	{
		// 설치 중단
		IsBombSetting = false;

		// 애니메이션 변경
		ChangePosture(static_cast<EPlayerPosture>(PrevItemIndex));
	}

	// 설치 시간 초기화

}

void ATestCharacter::BombSetComplete_Implementation()	// => 메인에 추후 이전해야 함 (24.07.31 수정 및 테스팅 중)
{
	IsBombSetting = false;
}

void ATestCharacter::ChangeMontage_Implementation(bool _IsFireEnd) // => 매인 적용.
{
	if (_IsFireEnd == false)
	{
		switch (PostureValue)
		{
		case EPlayerPosture::Rifle1:
			UpperStateValue = EPlayerUpperState::Rifle_Attack;
			break;
		case EPlayerPosture::Rifle2:
			UpperStateValue = EPlayerUpperState::Rifle_Attack;
			break;
		case EPlayerPosture::Melee:
			UpperStateValue = EPlayerUpperState::Melee;
			break;
		case EPlayerPosture::Drink:
			UpperStateValue = EPlayerUpperState::Drink;
			break;
		case EPlayerPosture::Bomb:
			UpperStateValue = EPlayerUpperState::Bomb;
			break;
		case EPlayerPosture::Barehand:
			UpperStateValue = EPlayerUpperState::Barehand;
			break;
		case EPlayerPosture::SlotMax:
			break;
		default:
			break;
		}
		PlayerAnimInst->ChangeAnimation(UpperStateValue);
		FPVPlayerAnimInst->ChangeAnimation(UpperStateValue);
		ClientChangeMontage(false);
	}
	else // FireEnd
	{
		UpperStateValue = EPlayerUpperState::Rifle_Idle;
		PlayerAnimInst->ChangeAnimation(UpperStateValue);
		FPVPlayerAnimInst->ChangeAnimation(UpperStateValue);
		ClientChangeMontage(true);
	}
}

void ATestCharacter::ClientChangeMontage_Implementation(bool _IsFireEnd) // => 매인 적용.
{
	if (_IsFireEnd == false)
	{
		switch (PostureValue)
		{
		case EPlayerPosture::Rifle1:
			UpperStateValue = EPlayerUpperState::Rifle_Attack;
			break;
		case EPlayerPosture::Rifle2:
			UpperStateValue = EPlayerUpperState::Rifle_Attack;
			break;
		case EPlayerPosture::Melee:
			UpperStateValue = EPlayerUpperState::Melee;
			break;
		case EPlayerPosture::Drink:
			UpperStateValue = EPlayerUpperState::Drink;
			break;
		case EPlayerPosture::Bomb:
			UpperStateValue = EPlayerUpperState::Bomb;
			break;
		case EPlayerPosture::Barehand:
			UpperStateValue = EPlayerUpperState::Barehand;
			break;
		case EPlayerPosture::SlotMax:
			break;
		default:
			break;
		}
		PlayerAnimInst->ChangeAnimation(UpperStateValue);
		FPVPlayerAnimInst->ChangeAnimation(UpperStateValue);
	}
	else // FireEnd
	{
		UpperStateValue = EPlayerUpperState::Rifle_Idle;
		PlayerAnimInst->ChangeAnimation(UpperStateValue);
		FPVPlayerAnimInst->ChangeAnimation(UpperStateValue);
	}
}

void ATestCharacter::ChangeState_Implementation(EPlayerState _Type)
{
	StateValue = _Type;
}

void ATestCharacter::ChangePosture_Implementation(EPlayerPosture _Type)	// => 메인으로 이전해야 함 (24.07.30 수정 중)
{
	if (_Type == EPlayerPosture::Barehand)			
	{
		// 1. Barehand => 맨손 자세로 변경
		PostureValue = _Type;
		PrevItemIndex = CurItemIndex;
		CurItemIndex = -1;

		// 아이템 메시 visibility 끄기
		ItemSocketMesh->SetVisibility(false);
		FPVItemSocketMesh->SetVisibility(false);
	}
	else
	{
		// 2. Rifle1, Rifle2, Melee, Drink, Bomb => 아이템을 든 자세로 변경
		int ItemSlotIndex = static_cast<int>(_Type);
		if (IsItemIn[ItemSlotIndex] == false)
		{
#ifdef WITH_EDITOR
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), ItemSlotIndex + 1));
#endif // WITH_EDITOR
			return;
		}
		PostureValue = _Type;
		PrevItemIndex = CurItemIndex;
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

void ATestCharacter::ChangeLowerState_Implementation(EPlayerLowerState _LowerState) // => 매인 적용.
{
	LowerStateValue = _LowerState;
}

void ATestCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir) // => 매인 적용.
{
	DirValue = _Dir;
}

void ATestCharacter::ChangeIsFaint_Implementation()
{
	if (true == IsFaint)
	{
		IsFaint = false;
	}
	else
	{
		IsFaint = true;
	}
}

void ATestCharacter::CheckItem() // => 메인 수정 필요 (24.07.30 DebugMessage 부분 수정됨)
{
	// 맵에 아이템이 없을 경우.
	if (nullptr == GetMapItemData)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There is no item to check.")));
#endif // WITH_EDITOR
		return;
	}

	AMapObjectBase* GetMapItem = Cast<AMapObjectBase>(GetMapItemData);
	if (nullptr != GetMapItem)
	{
		// 1. 맵오브젝트일 경우
		InteractObject(GetMapItem);
	}
	else
	{
		// 2. 주울 수 있는 아이템일 경우
		PickUpItem();
	}
}

void ATestCharacter::InteractObject_Implementation(AMapObjectBase* _MapObject)	// => 메인 이전 필요 (24.07.31 수정 중)
{
	// Door일 경우 : 상호작용은 Switch가 발동시키므로 return


	// Area일 경우 : 상호작용은 플레이어쪽에서 처리해야 하므로 return
	ADoorObject* DoorObject = Cast<ADoorObject>(_MapObject);
	if (nullptr != DoorObject)
	{
		return;
	}

	// Bomb일 경우 : 인벤토리에 아이템 집어넣기, 맵에서 아이템을 삭제
	ABomb* BombObject = Cast<ABomb>(_MapObject);
	if (nullptr != BombObject)
	{
		PickUpItem();
		return;
	}

	// 그 외 맵오브젝트(Switch 등)일 경우 : 상호작용 발동
	_MapObject->InterAction();
}

void ATestCharacter::PickUpItem_Implementation() // => 메인 수정 필요 (24.07.30 수정됨)
{
	// Overlap된 아이템의 Tag 이름을 통해 FName을 가져온다.
	FString TagName = "";
	for (size_t i = 0; i < GetMapItemData->Tags.Num(); i++)
	{
		TagName = GetMapItemData->Tags[i].ToString();
	}
	FName ItemStringToName = FName(*TagName);			// 아이템 이름

	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(ItemStringToName);

	EPlayerPosture ItemType = ItemData->GetType();		// 아이템 타입

	if (ItemType == EPlayerPosture::Rifle1)	// Rifle 아이템을 줍는 경우
	{
		if (false == IsItemIn[static_cast<int>(EPlayerPosture::Rifle1)])
		{
			// 1번 슬롯이 비어있는 경우 => 1번 슬롯
			ItemSetting(ItemStringToName, 0);
		}
		else if (true == IsItemIn[static_cast<int>(EPlayerPosture::Rifle1)] && false == IsItemIn[static_cast<int>(EPlayerPosture::Rifle2)])
		{
			// 1번 슬롯은 비어있지 않고, 2번 슬롯만 비어있는 경우 => 2번 슬롯
			ItemSetting(ItemStringToName, 1);
		}
		else
		{
			// 1번 슬롯도 2번 슬롯도 비어있지 않을 경우
			if (PostureValue == EPlayerPosture::Rifle1 || PostureValue == EPlayerPosture::Rifle2)
			{
				// 아이템을 줍기 직전에 1번 또는 2번 아이템을 손에 들고 있었다면 => 각각 1번 또는 2번 슬롯
				ItemSetting(ItemStringToName, static_cast<int>(PostureValue));
			}
			else
			{
				// 아이템을 줍기 직전에 맨손이거나, 3번 아이템을 손에 들고 있었다면 => 1번 슬롯
				ItemSetting(ItemStringToName, 0);
			}
		}
	}
	else	// Rifle이 아닌 아이템을 줍는 경우
	{
		ItemSetting(ItemStringToName, static_cast<int>(ItemType));
	}
	/*
		// 게임 플레이 진행 단계 업데이트
		if (EPlayerPosture::Rifle1 == ItemType
			|| EPlayerPosture::Melee == ItemType
			|| EPlayerPosture::Bomb == ItemType)
		{
			AMainGameState* CurGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

			if (nullptr == CurGameState)
			{
				UE_LOG(PlayerLog, Fatal, TEXT("GameState Is Nullptr"));
				return;
			}

			switch (ItemType)
			{
			case EPlayerPosture::Rifle1:
			case EPlayerPosture::Bomb:
				CurGameState->AddArmoryWeaponNum(ItemType);
				break;
			case EPlayerPosture::Melee:
				CurGameState->AddMeleeNum();
				break;
			default:
				break;
			}
		}
	}
	*/

	// Widget CallBack
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	if (nullptr != Con)
	{
		Con->FGetItemToWidget_Test.Execute();
	}
}

void ATestCharacter::ItemSetting(FName _TagName, int _SlotIndex) // => 메인 수정 필요 (24.07.31 수정됨)
{
	// ItemName에 맞는 아이템 정보를 DT에서 가져온다.
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(_TagName);
	EPlayerPosture ItemType = static_cast<EPlayerPosture>(_SlotIndex);

	// 이미 인벤토리에 같은 이름을 가진 아이템이 있을 경우.
	if (ItemSlot[_SlotIndex].Name == _TagName)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("The same item is already in inventory. (Index : %d)"), _SlotIndex + 1));
#endif // WITH_EDITOR
		return;
	}

	// 이미 인벤토리에 같은 타입의 아이템이 있을 경우.
	if (IsItemIn[_SlotIndex] == true)
	{
		DropItem(_SlotIndex);
	}

	// Data Table에 있는 아이템 정보 가져오기.
	int ItemReloadNum = ItemData->GetReloadNum();		// 무기 장전 단위 (30, 40)	// -1일 경우 총기류 무기가 아님
	int ItemDamage = ItemData->GetDamage();				// 무기 공격력				// 0일 경우 무기가 아님
	UStaticMesh* ItemMeshRes = ItemData->GetResMesh();	// 스태틱 메시 리소스
	FVector ItemRelLoc = ItemData->GetRelLoc();			// 스태틱 메시 컴포넌트 상대적 위치
	FRotator ItemRelRot = ItemData->GetRelRot();		// 스태틱 메시 컴포넌트 상대적 회
	FVector ItemRelScale = ItemData->GetRelScale();		// 스태틱 메시 컴포넌트 상대적 크기

	// 인벤토리에 아이템 넣기.
	IsItemIn[_SlotIndex] = true;

	ItemSlot[_SlotIndex].Name = _TagName;
	ItemSlot[_SlotIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[_SlotIndex].ReloadLeftNum = ItemReloadNum;
	ItemSlot[_SlotIndex].Damage = ItemDamage;
	ItemSlot[_SlotIndex].MeshRes = ItemMeshRes;
	ItemSlot[_SlotIndex].RelLoc = ItemRelLoc;
	ItemSlot[_SlotIndex].RelRot = ItemRelRot;
	ItemSlot[_SlotIndex].RelScale = ItemRelScale;

#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Picked up new item! (Index : %d)"), _SlotIndex + 1));
#endif // WITH_EDITOR

	// Map에 있는 아이템 삭제.
	GetMapItemData->Destroy();

	// 아이템 Type에 따른 애니메이션 자세 변화. (ItemType이 Rifle1, Rifle2, Melee일 경우만)
	if (ItemType == EPlayerPosture::Rifle1 || ItemType == EPlayerPosture::Rifle2 || ItemType == EPlayerPosture::Melee)
	{
		ChangePosture(ItemType);
	}
}

void ATestCharacter::DropItem_Implementation(int _SlotIndex) // => 메인 수정 필요 (24.07.30 DebugMessage 부분 수정됨)
{
	// DropItem 할 수 없는 경우 1: 맨손일 때
	if (CurItemIndex == -1)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (Current posture is 'Barehand')")));
#endif // WITH_EDITOR
		return;
	}

	// DropItem 할 수 없는 경우 2: (그럴리는 없겠지만) 현재 Posture에 해당하는 무기가 인벤토리에 없을 때
	if (IsItemIn[CurItemIndex] == false)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (The item slot is empty)")));
#endif // WITH_EDITOR
		return;
	}

	// 떨어트릴 아이템을 Actor로 생성
	FName ItemName = ItemSlot[CurItemIndex].Name;
	// UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld()); << 매인에는 이렇게 적용됨.
	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FItemDataRow* ItemBase = MainGameInst->GetItemData(ItemName);
	FTransform BoneTrans = GetMesh()->GetBoneTransform(FName("RightHand"), ERelativeTransformSpace::RTS_World); // 메인 적용.(07/29)

	// Spawn
	AActor* DropItem = GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), BoneTrans);

	// 아이템을 앞으로 던지기 (미완)
	//GetMesh()->SetSimulatePhysics(true);
	FVector ImpulseVector = GetActorForwardVector() * 1000.0f;
	GetMesh()->AddImpulse(ImpulseVector, FName("RightHand"), false);

	// 손에 들고 있던 아이템을 인벤토리에서 삭제
	DeleteItem(CurItemIndex);

	// 자세를 맨손으로 변경
	ChangePosture(EPlayerPosture::Barehand);
}

void ATestCharacter::DeleteItem(int _Index)
{
	FItemInformation NewSlot;
	ItemSlot[_Index] = NewSlot;
	IsItemIn[_Index] = false;
}

void ATestCharacter::ChangePOV()	// => 메인캐릭터로 이전해야 함 (24.07.29 수정 중) => 메인 적용.
{
	if (IsFPV)	// 일인칭 -> 삼인칭
	{
		// SpringArm Component 위치 수정.
		//SpringArmComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SpringArmComponent->TargetArmLength = 300.0f;
		SpringArmComponent->SetRelativeLocation(CameraRelLoc);

		// Character Mesh 전환.
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
		// SpringArm Component 위치 수정.
		//SpringArmComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("SpringArmSocket"));
		SpringArmComponent->TargetArmLength = 0.0f;
		switch (LowerStateValue)
		{
		case EPlayerLowerState::Idle:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc);
			break;
		case EPlayerLowerState::Crouch:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc_Crouch);
			break;
		default:
			break;
		}

		// Character Mesh 전환.
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

void ATestCharacter::CharacterReload() // => 매인 적용.
{
	if (-1 == CurItemIndex)
	{
		return;
	}
	ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	
	/* // Main
	// Widget 숨기기
	Reload_Widget->SetVisibility(ESlateVisibility::Hidden);

	// 총알 데이터 설정.
	ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;

	// 변경된 총알 데이터 호출.
	AMainPlayerController* Con = Cast<AMainPlayerController>(GetController());
	if (nullptr != Con)
	{
		Con->FCharacterToReload.Execute(); // Execute -> Delegate 실행.
	}
	*/
}

void ATestCharacter::MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision) // => 매인 적용.
{
	GetMapItemData = _OtherActor;
}

void ATestCharacter::MapItemOverlapEnd() // => 매인 적용.
{
	if (nullptr != GetMapItemData)
	{
		GetMapItemData = nullptr;
	}
}

void ATestCharacter::CrouchCameraMove() // => 매인에 적용 필요 (24.07.29 수정됨) => 메인 적용.
{
	if (IsFPV)
	{
		switch (LowerStateValue)
		{
		case EPlayerLowerState::Idle:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc_Crouch);
			break;
		case EPlayerLowerState::Crouch:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc);
			break;
		default:
			break;
		}
	}
}

void ATestCharacter::NetCheck() // => 매인 적용.
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
		//MyMaxHp = Inst->GetPlayerData(FName("TestPlayer"))->GetHp();

		// UGameplayStatics::GetPlayerPawn(Token)
	}
	else // client
	{

	}
}

void ATestCharacter::SendTokenToHpBarWidget() // => 매인 적용 진행 중.(HUD, Widget 대기중.)
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

void ATestCharacter::UpdatePlayerHp(float _DeltaTime) // => 매인 적용 진행 중.(HUD, Widget 대기중.)
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

	//CurHp = MyTestPlayerState->GetPlayerHp();

	ATestPlayHUD* PlayHUD = Cast<ATestPlayHUD>(MyController->GetHUD());
	if (nullptr != PlayHUD && Token != -1)
	{
		UTestHpBarUserWidget* MyHpWidget = Cast<UTestHpBarUserWidget>(PlayHUD->GetWidget(EUserWidgetType::HpBar));
		FString TestName = "CORORO_" + FString::FromInt(Token);
		MyHpWidget->NickNameUpdate(Token, FText::FromString(TestName));
		MyHpWidget->HpbarUpdate(Token, GetHp, 100.0f);
	}
}

void ATestCharacter::SettingPlayerState_Implementation()
{
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	if (nullptr == Con)
	{
		int a = 0;
		return;
	}

	ATestPlayerState* ThisPlayerState = Cast<ATestPlayerState>(Con->PlayerState);
	if (nullptr == ThisPlayerState)
	{
		int a = 0;
		return;
	}

	ThisPlayerState->InitPlayerData();
}

void ATestCharacter::ShowMuzzle()
{
	FVector ShowPoint = GetMesh()->GetSocketLocation(FName("MuzzleSocket"));
	MuzzleParticleComponent->SetRelativeLocation(ShowPoint);
	MuzzleParticleComponent->SetVisibility(true);
}

void ATestCharacter::ShowEndMuzzle()
{
	MuzzleParticleComponent->SetVisibility(false);
}
