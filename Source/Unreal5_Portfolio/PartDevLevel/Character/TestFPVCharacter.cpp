// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/TestFPVCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "TimerManager.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"
#include "PartDevLevel/Character/TestFPVPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/DataTable/ItemDataRow.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "PartDevLevel/Character/PlayerAnimInstance.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "TestLevel/UI/TestPlayHUD.h"
#include "TestLevel/UI/TestHpBarUserWidget.h"
#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"
#include "MainGameLevel/Object/ItemBase.h"
#include "MainGameLevel/Object/AreaObject.h"
#include "MainGameLevel/Object/DoorObject.h"
#include "MainGameLevel/Particles/MuzzleParticleActor.h"

// Sets default values
ATestFPVCharacter::ATestFPVCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->bHiddenInSceneCapture = true;

	// Item Mesh
	ItemSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSocketMesh"));
	ItemSocketMesh->SetupAttachment(GetMesh(), FName("ItemSocket"));
	ItemSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ItemSocketMesh->SetGenerateOverlapEvents(true);
	ItemSocketMesh->SetOwnerNoSee(true);
	ItemSocketMesh->SetVisibility(false);
	ItemSocketMesh->SetIsReplicated(true);
	ItemSocketMesh->bHiddenInSceneCapture = true;

	// SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc);
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = true;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	// FPV Character Mesh
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetRelativeLocation(FVector(-10.0f, 0.0f, -160.0f));
	FPVMesh->SetOwnerNoSee(false);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// FPV Item Mesh
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
	GetMapItemCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("GetMapItemCollisionComponent"));
	GetMapItemCollisionComponent->SetupAttachment(RootComponent);
	GetMapItemCollisionComponent->SetRelativeLocation(FVector(60.0, 0.0, -5.0f));
	GetMapItemCollisionComponent->SetBoxExtent(FVector(60.0f, 30.0f, 100.0f));
	GetMapItemCollisionComponent->SetCollisionProfileName(FName("MapItemSearch"));

	// Hand Attack Component
	HandAttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hand Attack Comp"));
	HandAttackComponent->SetupAttachment(GetMesh());
	HandAttackComponent->SetRelativeLocation({ 0.0f, 100.0f, 120.0f });
	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));

	// MiniMap Icon Component
	MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	MinimapIconComponent->SetupAttachment(RootComponent);
	MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// HeadName Component
	HeadNameComponent = CreateDefaultSubobject<UHeadNameWidgetComponent>(TEXT("HeadNameWidgetComponent"));
	HeadNameComponent->SetupAttachment(RootComponent);
	HeadNameComponent->SetOwnerNoSee(true);
	HeadNameComponent->bHiddenInSceneCapture = true;

	// Inventory			// => 메인 수정 필요 (24.08.06 수정됨) [자식]
	for (size_t i = 0; i < 4; i++)
	{
		FFPVItemInformation NewSlot;
		ItemSlot.Push(NewSlot);
	}
}

void ATestFPVCharacter::HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision) // => 매인 캐릭터에 적용.
{
	{
		//ATestMonsterBase* Monster = Cast<ATestMonsterBase>(_OtherActor);
		//if (nullptr != Monster)
		//{
		//	Monster->Damaged(150.0f);
		//}
	}

	{
		//ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(_OtherActor);
		//if (nullptr != BossMonster)
		//{
		//	BossMonster->Damaged(150.0f);
		//}
	}
}

// 메인 플레이어 추가 필요 코드 (태환) 07/24 => 매인 적용.
void ATestFPVCharacter::PostInitializeComponents()
{
	if (GetWorld()->WorldType == EWorldType::Game
		|| GetWorld()->WorldType == EWorldType::PIE)
	{
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		if (nullptr == MainGameInst)
		{
			return;
		}

		// FName을 가져오는 기능이 필요하다.
		//FName PlayerID = MainGameInst->GetUIToSelectCharacter();

		// 스켈레탈 메쉬 선택
		USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);

		// 팔 메쉬 선택 (메인 추가 필요)
		USkeletalMesh* FPVSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerFPVPlayerSkeletalMesh();
		FPVMesh->SetSkeletalMesh(FPVSkeletalMesh);

		// ABP 선택
		UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}

	Super::PostInitializeComponents();
}

void ATestFPVCharacter::AnimationEnd() 
{
	PlayerAnimInst->ChangeAnimation(IdleDefault);
	FPVPlayerAnimInst->ChangeAnimation(IdleDefault);

	// 동기화 이슈 발생.
	// ChangeMontage(IdleDefault);
}

// Called when the game starts or when spawned
void ATestFPVCharacter::BeginPlay()	// => 메인 수정 필요 (24.08.01 수정, 추가된 요소 있음)
{
	NetCheck();
	Super::BeginPlay();

	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	// PlayerState => 초기화
	SettingPlayerState();

	// 몽타주 변경에 필요한 세팅 추가 필요 (태환) // => 매인 적용.
	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	FPVPlayerAnimInst = Cast<UPlayerAnimInstance>(FPVMesh->GetAnimInstance());

	// GetMapItemCollisionComponent => MapItem과 Overlap될 시 실행할 함수 바인딩
	GetMapItemCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATestFPVCharacter::MapItemOverlapStart);
	GetMapItemCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATestFPVCharacter::MapItemOverlapEnd);


	//double MyVelocity = UKismetMathLibrary::VSizeXY(GetVelocity());
	//UCharacterMovementComponent* MyMovementComponent = GetCharacterMovement();
	//MyMovementComponent->IsFalling();

	ChangeMontage(EPlayerUpperState::UArm_Idle);

	// Call Back
	/*PlayerAnimInst->SetEndCallBack(EPlayerUpperState::Rifle_Attack,
		[=, this](uint8 _Type, UAnimMontage* _Mon)
		{
			AttackEndCheck();
		});

	PlayerAnimInst->SetEndCallBack(EPlayerUpperState::Melee_Attack,
		[=, this](uint8 _Type, UAnimMontage* _Mon)
		{
			AttackEndCheck();
		});

	PlayerAnimInst->SetEndCallBack(EPlayerUpperState::UArm_Attack,
		[=, this](uint8 _Type, UAnimMontage* _Mon)
		{
			AttackEndCheck();
		});

	PlayerAnimInst->SetEndCallBack(EPlayerUpperState::Drink,
		[=, this](uint8 _Type, UAnimMontage* _Mon)
		{
			AttackEndCheck();
		});*/
}

// Called every frame
void ATestFPVCharacter::Tick(float DeltaTime)
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
	// GameState 변수 출력용 TestCode (이건 메인에 옮기시지 않아도 됩니다!! - 경윤 -)
	{
		AMainGameState* CurGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

		if (nullptr == CurGameState)
		{
			return;
		}
		int CurPlayerNum = CurGameState->GetPlayerCount();
		FString PNString = FString::FromInt(CurPlayerNum);
		UMainGameBlueprintFunctionLibrary::DebugTextPrint(GetWorld(), FString(TEXT("CurPlayerCount = ")) + PNString);

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

	// Debugging
	//DefaultRayCast(DeltaTime);
	//float ts = GetWorld()->GetDeltaSeconds();
	//TArray<FFPVItemInformation> I = ItemSlot;
	//int c = CurItemIndex;
	//AGameModeBase* Ptr = GetWorld()->GetAuthGameMode();
}

void ATestFPVCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// AnimInstance
	DOREPLIFETIME(ATestFPVCharacter, LowerStateValue);	// => 매인 적용.
	DOREPLIFETIME(ATestFPVCharacter, DirValue);			// => 매인 적용.
	DOREPLIFETIME(ATestFPVCharacter, IsFaint);			// 7/26 추가
	DOREPLIFETIME(ATestFPVCharacter, IsBombSetting);	// => 메인에 이전 필요 (24.07.29 추가됨)
	DOREPLIFETIME(ATestFPVCharacter, IdleDefault);

	// Inventory
	//DOREPLIFETIME(ATestFPVCharacter, ItemSlot);		// => 메인 삭제 필요 (24.08.06 삭제됨)
	//DOREPLIFETIME(ATestFPVCharacter, IsItemIn);		// => 메인 삭제 필요 (24.08.06 삭제됨)

	// Item
	//DOREPLIFETIME(ATestFPVCharacter, RayCastToItemName); // 사용 안함.

	// Server?
	DOREPLIFETIME(ATestFPVCharacter, Token); // => 매인 적용.
}

void ATestFPVCharacter::FireRayCast_Implementation() // => 메인 수정 필요 (24.07.30 DebugMessage 부분 수정됨)
{
	if (CurItemIndex == -1 || CurItemIndex == 2)
	{
		return;
	}

	if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	{
		ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	}

	ATestFPVPlayerController* Con = Cast<ATestFPVPlayerController>(GetController());
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
				//ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Hit.GetActor()); // [Main] ABasicMonsterBase
				//if (nullptr != Monster)
				//{
				//	Monster->Damaged(ItemSlot[CurItemIndex].Damage);
				//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : %d"), *Monster->GetName(), ItemSlot[CurItemIndex].Damage));
				//}
			}
			{
				//ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(Hit.GetActor());
				//if (nullptr != BossMonster)
				//{
				//	BossMonster->Damaged(ItemSlot[CurItemIndex].Damage);
				//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s got damage : %d"), *BossMonster->GetName(), ItemSlot[CurItemIndex].Damage));
				//}
			}
		}
	}
}

void ATestFPVCharacter::Drink()
{
	ChangeMontage(EPlayerUpperState::Drink);

	// 음료 아이템이 없다면 return
//	if (false == IsItemIn[3])
//	{
//#ifdef WITH_EDITOR
//		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), 4));
//#endif
//		return;
//	}

	// 애니메이션 변경
	//ChangePosture(EPlayerPosture::Drink);

//	// 음료 아이템 삭제
//	DeleteItem(3);
//
//	// 실질적인 플레이어 HP 회복
//	ATestPlayerState* MyTestPlayerState = GetPlayerState<ATestPlayerState>();
//	if (nullptr == MyTestPlayerState)
//	{
//		return;
//	}
//	MyTestPlayerState->HealHp();
//
//#ifdef WITH_EDITOR
//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString(TEXT("HP recovered!")));
//#endif
}

// 노티파이
void ATestFPVCharacter::DrinkComplete_Implementation()			// => 메인에 이전 필요 (24.08.01 수정됨)
{

	ChangeMontage(IdleDefault);
}

void ATestFPVCharacter::ChangeHandAttackCollisionProfile(FName _Name)
{
	HandAttackComponent->SetCollisionProfileName(_Name);
}

void ATestFPVCharacter::BombSetStart_Implementation()			// => 메인 수정 필요 (24.08.06 인벤토리에 있는지 검사하는 부분 수정됨)
{
	// 폭탄 아이템이 없다면 return
	if (false == ItemSlot[static_cast<int>(EItemType::Bomb)].IsItemIn)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), 4));
#endif
		return;
	}

	// 폭탄 설치 가능한 Area가 아닐 경우 return
	AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);	// 240801 AreaObject 추가로 해당 클래스 변경
	if (nullptr == AreaObject)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("You have to set the bomb in proper area.")));
#endif
		return;
	}

	// 폭탄 설치 가능한 것으로 판단, 설치 시작
	IsBombSetting = true;
	AreaObject->ResetBombTime();
#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString(TEXT("Bomb setting start.")));
#endif

	// 애니메이션 변경
	ChangeMontage(EPlayerUpperState::Bomb);
}

void ATestFPVCharacter::BombSetTick_Implementation()		// => 메인에 이전 필요 (24.08.01 수정됨)
{
	if (true == IsBombSetting)
	{
		AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);	// 240801 AreaObject 추가로 해당 클래스 변경
		if (nullptr == AreaObject)
		{
#ifdef WITH_EDITOR
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("You have to set the bomb in proper area.")));
#endif
			return;
		}

		// 설치 시간 카운트가 끝났을 경우
		if (0 >= AreaObject->GetInstallBombTime())
		{
			BombSetComplete();
		}

		// 설치 시간 카운팅
		AreaObject->InstallBomb(GetWorld()->GetDeltaSeconds());
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%f seconds left..."), AreaObject->GetInstallBombTime()));
#endif
	}
}

void ATestFPVCharacter::BombSetCancel_Implementation()		// => 메인에 이전 필요 (24.08.01 수정됨)
{
	if (true == IsBombSetting)
	{
		// 폭탄 설치 중단
		IsBombSetting = false;
		AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);	// 240801 AreaObject 추가로 해당 클래스 변경
		if (nullptr != AreaObject)
		{
			AreaObject->ResetBombTime();
		}

		// 이전 자세로 애니메이션 변경
		ChangeMontage(IdleDefault);
	}
}

void ATestFPVCharacter::BombSetComplete_Implementation()	// => 메인 수정 필요 (24.08.06 인벤토리에서 아이템 삭제하는 부분 수정됨)
{
	// 폭탄 설치 완료
	IsBombSetting = false;

	AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);	// 24-08-01 AreaObject 추가로 해당 클래스 변경
	if (nullptr != AreaObject)
	{
		AreaObject->InterAction();
	}
#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString(TEXT("Bomb setting completed!")));
#endif // WITH_EDITOR

	// 인벤토리에서 폭탄 아이템 삭제
	DeleteItemInfo(static_cast<int>(EItemType::Bomb));

	// 이전 자세로 애니메이션 변경
	//ChangePosture(PrevPostureValue);
	ChangeMontage(IdleDefault);
}

void ATestFPVCharacter::ChangeMontage_Implementation(EPlayerUpperState _UpperState, bool IsSet)
{
	if (true == IsSet)
	{
		IdleDefault = _UpperState;
	}

	PlayerAnimInst->ChangeAnimation(_UpperState);
	FPVPlayerAnimInst->ChangeAnimation(_UpperState);
	ClientChangeMontage(_UpperState);
}

void ATestFPVCharacter::ClientChangeMontage_Implementation(EPlayerUpperState _UpperState)
{
	PlayerAnimInst->ChangeAnimation(_UpperState);
	FPVPlayerAnimInst->ChangeAnimation(_UpperState);
}

void ATestFPVCharacter::SettingItemSocket(int _InputKey)		// => 메인에 이전 필요 (24.08.06 추가됨)
{
	if (-1 == _InputKey)
	{
		// ItemSocket의 visibility 끄기
		SetItemSocketVisibility(false);
		return;
	}

	UStaticMesh* ItemMeshRes = ItemSlot[_InputKey].MeshRes;
	FVector ItemRelLoc = ItemSlot[_InputKey].RelLoc;
	FRotator ItemRelRot = ItemSlot[_InputKey].RelRot;
	FVector ItemRelScale = ItemSlot[_InputKey].RelScale;

	// ItemSocket의 static mesh 세팅
	SetItemSocketMesh(ItemMeshRes, ItemRelLoc, ItemRelRot, ItemRelScale);

	// ItemSocket의 visibility 켜기
	SetItemSocketVisibility(true);
}

void ATestFPVCharacter::SetItemSocketMesh_Implementation(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale)
{
	// static mesh 세팅
	ItemSocketMesh->SetStaticMesh(_ItemMeshRes);
	FPVItemSocketMesh->SetStaticMesh(_ItemMeshRes);

	// transform 세팅
	ItemSocketMesh->SetRelativeLocation(_ItemRelLoc);
	FPVItemSocketMesh->SetRelativeLocation(_ItemRelLoc);

	ItemSocketMesh->SetRelativeRotation(_ItemRelRot);
	FPVItemSocketMesh->SetRelativeRotation(_ItemRelRot);

	ItemSocketMesh->SetRelativeScale3D(_ItemRelScale);
	FPVItemSocketMesh->SetRelativeScale3D(_ItemRelScale);
}

void ATestFPVCharacter::SetItemSocketVisibility_Implementation(bool _Visibility)
{
	ItemSocketMesh->SetVisibility(_Visibility);
	FPVItemSocketMesh->SetVisibility(_Visibility);
}

//void ATestFPVCharacter::ChangePosture_Implementation(EPlayerPosture _Type)	// => 메인으로 이전해야 함 (24.07.30 수정 중)
//{
//	PostureValue = _Type;
//	if (_Type == EPlayerPosture::Barehand)
//	{
//		// 1. Barehand => 맨손 자세로 변경
//		
//		// 이전 PostureValue를 저장.
//		PrevPostureValue = PostureValue;
//
//		// Anim Instance 값 설정.
//		PostureValue = _Type;
//		
//		// == 아이템 장착. ==
//		CurItemIndex = 5;
//
//		// 아이템 메시 visibility 끄기
//		ItemSocketMesh->SetVisibility(false);
//		FPVItemSocketMesh->SetVisibility(false);
//	}
//	else
//	{
//		// 2. Rifle1, Rifle2, Melee, Drink, Bomb => 아이템을 든 자세로 변경
//		int ItemSlotIndex = static_cast<int>(_Type);
//		if (IsItemIn[ItemSlotIndex] == false)
//		{
//#ifdef WITH_EDITOR
//			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("The item slot is empty. (Index : %d)"), ItemSlotIndex + 1));
//#endif // WITH_EDITOR
//			return;
//		}
//		// 이전 PostureValue를 저장.
//		PrevPostureValue = PostureValue;
//
//		// Anim Instance 값 설정.
//		PostureValue = _Type;
//		
//		// == 아이템 장착. ==
//		CurItemIndex = ItemSlotIndex;
//
//		// 아이템 static mesh 세팅
//		ItemSocketMesh->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);
//		FPVItemSocketMesh->SetStaticMesh(ItemSlot[CurItemIndex].MeshRes);
//
//		// 아이템 메시 transform 세팅
//		ItemSocketMesh->SetRelativeLocation(ItemSlot[CurItemIndex].RelLoc);
//		FPVItemSocketMesh->SetRelativeLocation(ItemSlot[CurItemIndex].RelLoc);
//
//		ItemSocketMesh->SetRelativeRotation(ItemSlot[CurItemIndex].RelRot);
//		FPVItemSocketMesh->SetRelativeRotation(ItemSlot[CurItemIndex].RelRot);
//
//		ItemSocketMesh->SetRelativeScale3D(ItemSlot[CurItemIndex].RelScale);
//		FPVItemSocketMesh->SetRelativeScale3D(ItemSlot[CurItemIndex].RelScale);
//
//		// 아이템 메시 visibility 켜기
//		ItemSocketMesh->SetVisibility(true);
//		FPVItemSocketMesh->SetVisibility(true);
//	}
//}

void ATestFPVCharacter::CrouchCameraMove() // => 매인에 적용 필요 (24.07.29 수정됨) => 메인 적용.
{
	// Controller의 Crouch 함수에서 호출.
	//if (IsFPV)
	if(PointOfView == EPlayerFPSTPSState::FPS)
	{
		switch (LowerStateValue)
		{
		case EPlayerLowerState::Idle:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc_Crouch);
			ChangeLowerState(EPlayerLowerState::Crouch);
			break;
		case EPlayerLowerState::Crouch:
			SpringArmComponent->SetRelativeLocation(FPVCameraRelLoc);
			ChangeLowerState(EPlayerLowerState::Idle);
			break;
		default:
			break;
		}
	}
	else if(PointOfView == EPlayerFPSTPSState::TPS)
	{
		switch (LowerStateValue)
		{
		case EPlayerLowerState::Idle:
			ChangeLowerState(EPlayerLowerState::Crouch);
			break;
		case EPlayerLowerState::Crouch:
			ChangeLowerState(EPlayerLowerState::Idle);
			break;
		default:
			break;
		}
	}
}

void ATestFPVCharacter::ChangeLowerState_Implementation(EPlayerLowerState _LowerState) // => 매인 적용.
{
	// L-Ctrl
	LowerStateValue = _LowerState;
}

void ATestFPVCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir) // => 매인 적용.
{
	if (IdleDefault == EPlayerUpperState::UArm_Idle)
	{
		switch (_Dir)
		{
		case EPlayerMoveDir::Forward:
			ChangeMontage(EPlayerUpperState::MoveForward);
			break;
		case EPlayerMoveDir::Back:
			ChangeMontage(EPlayerUpperState::MoveBack);
			break;
		case EPlayerMoveDir::Left:
			ChangeMontage(EPlayerUpperState::MoveLeft);
			break;
		case EPlayerMoveDir::Right:
			ChangeMontage(EPlayerUpperState::MoveRight);
			break;
		default:
			break;
		}
	}

	// W A S D
	DirValue = _Dir;
}

void ATestFPVCharacter::ChangeIsFaint_Implementation()
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

bool ATestFPVCharacter::IsItemInItemSlot(int _Index)
{
	return ItemSlot[_Index].IsItemIn;
}

void ATestFPVCharacter::CheckItem()	// => 메인 수정 필요 (24.08.02 PickUpItem 인자 추가됨)
{
	// 맵에 아이템이 없을 경우.
	if (nullptr == GetMapItemData)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There is no item to check.")));
#endif // WITH_EDITOR
		return;
	}

	AMapObjectBase* GetMapObject = Cast<AMapObjectBase>(GetMapItemData);
	if (nullptr != GetMapObject)
	{
		// 1. 맵오브젝트일 경우
		InteractObject(GetMapObject);
	}
	else
	{
		// 2. 주울 수 있는 아이템일 경우
		AItemBase* GetMapItem = Cast<AItemBase>(GetMapItemData);
		PickUpItem(GetMapItem);
	}
}

void ATestFPVCharacter::InteractObject_Implementation(AMapObjectBase* _MapObject)	// => 메인 이전 필요 (24.08.06 Bomb 부분 삭제됨)
{
	// Door일 경우 : 상호작용은 Switch가 발동시키므로 return
	ADoorObject* DoorObject = Cast<ADoorObject>(_MapObject);
	if (nullptr != DoorObject)
	{
		return;
	}

	// Area일 경우 : 상호작용은 플레이어쪽에서 처리해야 하므로 return	// 240801 AreaObject 추가로 해당 내용 추가되었습니다
	AAreaObject* AreaObject = Cast<AAreaObject>(_MapObject);
	if (nullptr != AreaObject)
	{
		return;
	}

	// 그 외 맵오브젝트(Switch 등)일 경우 : 상호작용 발동
	_MapObject->InterAction();
}

void ATestFPVCharacter::PickUpItem(AItemBase* _Item)	// => 메인 수정 필요 (24.08.06 수정됨)
{
	const FItemDataRow* ItemData = _Item->GetItemData();

	EItemType ItemType = ItemData->GetItemType();
	int ItemSlotIndex = static_cast<int>(ItemType);
	FName ItemName = *(ItemData->GetName());

	// 이미 같은 이름을 가진 아이템이 인벤토리에 있을 경우 return
	if (ItemName == ItemSlot[ItemSlotIndex].Name)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("The same item is already in inventory. (Index : %d)"), ItemSlotIndex + 1));
#endif // WITH_EDITOR
		return;
	}

	// 이미 같은 타입의 아이템이 인벤토리에 있을 경우 가지고 있던 아이템을 Drop
	if (true == ItemSlot[ItemSlotIndex].IsItemIn)
	{
		DropItem(ItemSlotIndex);
	}

	// 인벤토리에 PickUp한 아이템 정보 넣기
	ItemSlot[ItemSlotIndex].IsItemIn = true;								
	ItemSlot[ItemSlotIndex].Name = ItemName;								
	ItemSlot[ItemSlotIndex].ReloadMaxNum = ItemData->GetReloadNum();		// 무기 장전 단위	 (Max) (-1일 경우 총기류 무기가 아님)
	ItemSlot[ItemSlotIndex].ReloadLeftNum = ItemData->GetReloadNum();		// 무기 장전 단위	 (Left) (-1일 경우 총기류 무기가 아님)
	ItemSlot[ItemSlotIndex].Damage = ItemData->GetDamage();					// 무기 공격력 (0일 경우 무기가 아님)
	ItemSlot[ItemSlotIndex].MeshRes = ItemData->GetResMesh();				// 스태틱 메시 리소스
	ItemSlot[ItemSlotIndex].RelLoc = ItemData->GetRelLoc();					// ItemSocket, FPVItemSocket 상대적 위치
	ItemSlot[ItemSlotIndex].RelRot = ItemData->GetRelRot();					// ItemSocket, FPVItemSocket 상대적 회전
	ItemSlot[ItemSlotIndex].RelScale = ItemData->GetRelScale();				// ItemSocket, FPVItemSocket 상대적 크기

#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Picked up new item! (Index : %d)"), ItemSlotIndex + 1));
#endif // WITH_EDITOR

	// 필드에 존재하는 아이템 액터 삭제
	DestroyItem(_Item);

	// 애니메이션 업데이트
	ItemToCheckAnimation();
}

void ATestFPVCharacter::DropItem(int _SlotIndex)	// => 메인 수정 필요 (24.08.06 수정됨)
{
	CurItemIndex = 0;	// Testing

	// DropItem 할 수 없는 경우 1 : 맨손일 때
	if (CurItemIndex == -1)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (Current posture is 'Barehand')")));
#endif // WITH_EDITOR
		return;
	}

	// DropItem 할 수 없는 경우 2 : (그럴리는 없겠지만) 현재 Posture에 해당하는 무기가 인벤토리에 없을 때
	if (false == ItemSlot[CurItemIndex].IsItemIn)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (The item slot is empty)")));
#endif // WITH_EDITOR
		return;
	}
	
	// 떨어트릴 아이템을 스폰
	FName ItemName = ItemSlot[_SlotIndex].Name;
	FTransform SpawnTrans = GetActorTransform();
	SpawnTrans.SetTranslation(GetActorLocation() + (GetActorForwardVector() * 100.0f) + (GetActorUpVector() * 50.0f));

	SpawnItem(ItemName, SpawnTrans);

	// 아이템 앞으로 던지기 (수정 중)
	//GetMesh()->SetSimulatePhysics(true);
	//FVector ImpulseVector = GetActorForwardVector() * 1000.0f;
	//GetMesh()->AddImpulse(ImpulseVector, FName("RightHand"), false);

	// 인벤토리에서 버린 아이템 정보 삭제
	DeleteItemInfo(_SlotIndex);

#ifdef WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Drop the item. (Index : %d)"), _SlotIndex + 1));
#endif // WITH_EDITOR

	// 애니메이션 업데이트
	ItemToCheckAnimation();
	//ChangePosture(EPlayerPosture::Barehand);
	//ChangeMontage(EPlayerUpperState::UArm_Attack);
}

void ATestFPVCharacter::DestroyItem_Implementation(AItemBase* _Item)	// => 메인 이전 필요 (24.08.06 추가됨)
{
	// 필드에서 아이템 Destroy
	_Item->Destroy();
}

void ATestFPVCharacter::SpawnItem_Implementation(FName _ItemName, FTransform _SpawnTrans)	// => 메인 이전 필요 (24.08.06 추가됨)
{
	// 스폰할 아이템 정보 가져오기
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	const FItemDataRow* ItemData = MainGameInst->GetItemData(_ItemName);

	// 필드에 아이템 Spawn
	AItemBase* DropItem = GetWorld()->SpawnActor<AItemBase>(ItemData->GetItemUClass(), _SpawnTrans);
	UStaticMeshComponent* DropItemMeshComp = Cast<AItemBase>(DropItem)->GetStaticMeshComponent();
	DropItemMeshComp->SetSimulatePhysics(true);
}

void ATestFPVCharacter::DeleteItemInfo(int _Index)		// => 메인 수정 필요 (24.08.06 수정됨)
{
	FFPVItemInformation NewSlot;
	ItemSlot[_Index] = NewSlot;
}

void ATestFPVCharacter::ChangePOV()	// => 메인캐릭터로 이전해야 함 (24.07.29 수정 중) => 메인 적용.
{
	//if (IsFPV)	// 일인칭 -> 삼인칭
	if (PointOfView == EPlayerFPSTPSState::FPS)
	{
		// SpringArm Component 위치 수정.
		//SpringArmComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SpringArmComponent->TargetArmLength = 300.0f;
		SpringArmComponent->SetRelativeLocation(CameraRelLoc);

		// Character Mesh 전환.
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);

		// Item Mesh
		for (int i = 0; i < static_cast<int>(EPlayerUpperState::UArm_Attack); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(false);
			FPVItemSocketMesh->SetOwnerNoSee(true);
		}

		//IsFPV = false;
		PointOfView = EPlayerFPSTPSState::TPS;
	}
	else if(PointOfView == EPlayerFPSTPSState::TPS)	// 삼인칭 -> 일인칭
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
		for (int i = 0; i < static_cast<int>(EPlayerUpperState::UArm_Attack); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(true);
			FPVItemSocketMesh->SetOwnerNoSee(false);
		}

		//IsFPV = true;
		PointOfView = EPlayerFPSTPSState::FPS;
	}
}

void ATestFPVCharacter::CharacterReload() // => 매인 적용.
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

void ATestFPVCharacter::MapItemOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)	// => 메인 수정 필요 (24.08.02 AreaObject일 경우 조건 검사 부분 수정)
{
	GetMapItemData = OtherActor;

	ATestFPVPlayerController* MyController = Cast<ATestFPVPlayerController>(GetController());
	if (nullptr == MyController)
	{
		return;
	}

	ATestPlayHUD* PlayHUD = Cast<ATestPlayHUD>(MyController->GetHUD());
	if (nullptr == PlayHUD)
	{
		return;
	}

	AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);
	if (nullptr != AreaObject)
	{
		// Area일 경우 => "5번키를 눌러 상호작용"
		PlayHUD->UIOn(EUserWidgetType::Num5_Key);
		return;
	}

	// 그 외의 경우 => "E키를 눌러 상호작용"
	PlayHUD->UIOn(EUserWidgetType::E_Key);
}

void ATestFPVCharacter::MapItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)	// => 메인 수정 필요 (24.08.01 수정됨)
{
	if (nullptr != GetMapItemData)
	{
		GetMapItemData = nullptr;
	}

	ATestFPVPlayerController* MyController = Cast<ATestFPVPlayerController>(GetController());
	if (nullptr == MyController)
	{
		return;
	}

	ATestPlayHUD* PlayHUD = Cast<ATestPlayHUD>(MyController->GetHUD());
	if (nullptr == PlayHUD)
	{
		return;
	}

	// 켜져 있는 상호작용 관련 UI 모두 끄기
	PlayHUD->UIOff(EUserWidgetType::Num5_Key);
	PlayHUD->UIOff(EUserWidgetType::E_Key);
}


void ATestFPVCharacter::AttackCheck()
{
	// Mouse Left Button 

	switch (IdleDefault)
	{
	case EPlayerUpperState::UArm_Idle:
		ChangeMontage(EPlayerUpperState::UArm_Attack);
		break;
	case EPlayerUpperState::Rifle_Idle:
		ChangeMontage(EPlayerUpperState::Rifle_Attack);
		break;
	case EPlayerUpperState::Melee_Idle:
		ChangeMontage(EPlayerUpperState::Melee_Attack);
		break;
	default:
		break;
	}
}

void ATestFPVCharacter::AttackEndCheck()
{
	//ChangeMontage(IdleDefault);

	//UAnimMontage* GetCurMontage = GetCurrentMontage();
	//FName GetCurMontageName = GetCurMontage->GetFName();
	//// E_Fire_Stand_Montage
	//// E_BareHand_Attack_Montage

	//if ("E_Fire_Stand_Montage" == GetCurMontageName || "E_BareHand_Attack_Montage" == GetCurMontageName)
	//{
	//	// 노티파이 신호 조건?
	//	return;
	//}
	//else
	//{
	//	ChangeMontage(IdleDefault);
	//}
}

void ATestFPVCharacter::NetCheck() // => 매인 적용.
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

void ATestFPVCharacter::SendTokenToHpBarWidget() // => 매인 적용 진행 중.(HUD, Widget 대기중.)
{
	ATestFPVPlayerController* Con = Cast<ATestFPVPlayerController>(GetController());
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

void ATestFPVCharacter::UpdatePlayerHp(float _DeltaTime) // => 매인 적용 진행 중.(HUD, Widget 대기중.)
{
	ATestPlayerState* MyTestPlayerState = GetPlayerState<ATestPlayerState>();
	if (nullptr == MyTestPlayerState)
	{
		return;
	}

	ATestFPVPlayerController* MyController = Cast<ATestFPVPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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

void ATestFPVCharacter::SettingPlayerState_Implementation()
{
	ATestFPVPlayerController* Con = Cast<ATestFPVPlayerController>(GetController());
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

void ATestFPVCharacter::ShowMuzzle()
{
	FTransform CreatePosition = GetMesh()->GetBoneTransform(FName("RightHand"), ERelativeTransformSpace::RTS_World);
	GetWorld()->SpawnActor<AActor>(AMuzzleParticleActor::StaticClass(), CreatePosition);
}

void ATestFPVCharacter::ItemToCheckAnimation()
{

}