// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "TestPlayerController.h"
#include "MainGameLevel/Player/PlayerItemInformation.h"
#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "Components/SphereComponent.h"
#include "MainGameLevel/Player/MainPlayerState.h"

#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"
#include "PartDevLevel/Monster/Kraken/KrakenProjectile.h"

#include "MainGameLevel/Object/MapObjectBase.h"
#include "MainGameLevel/Object/DoorObject.h"
#include "MainGameLevel/Object/Bomb.h"
#include "MainGameLevel/Object/AreaObject.h"

#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"
#include "MainGameLevel/UI/InGame/MainGameHUD.h"
#include "MainGameLevel/UI/Title/MainTitleHUD.h"
#include "PartDevLevel/UI/GetItem/GetItem_UserWidget.h"
#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "testLevel/UI/TestHpBarUserWidget.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "TestPlayerState.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// == Init ==

	// character Mesh
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->bHiddenInSceneCapture = true;

	// 아이템 장착 소켓 초기화.
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

	// Map Item 
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

	// MinimapIcon Component
	MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	MinimapIconComponent->SetupAttachment(RootComponent);
	MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// HeadName Component
	HeadNameComponent = CreateDefaultSubobject<UHeadNameWidgetComponent>(TEXT("HeadNameWidgetComponent"));
	HeadNameComponent->SetupAttachment(RootComponent);
	HeadNameComponent->SetOwnerNoSee(true);
	HeadNameComponent->bHiddenInSceneCapture = true;

	// Inventory
	for (size_t i = 0; i < 4; i++)
	{
		FPlayerItemInformation NewSlot;
		ItemSlot.Push(NewSlot);
	}
}

void ATestCharacter::PostInitializeComponents() // FName 부분 수정 필요.
{
	if (GetWorld()->WorldType == EWorldType::Game
		|| GetWorld()->WorldType == EWorldType::PIE)
	{
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		if (nullptr == MainGameInst)
		{
			return;
		}

		GetSetSelectCharacter(MainGameInst);
		if (UIToSelectCharacter == "")
		{
			UIToSelectCharacter = "TestPlayer"; // test
		}

		// 스켈레탈 메쉬 선택
		//USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerSkeletalMesh();
		USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(UIToSelectCharacter)->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);


		//USkeletalMesh* FPVSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerFPVPlayerSkeletalMesh();
		USkeletalMesh* FPVSkeletalMesh = MainGameInst->GetPlayerData(UIToSelectCharacter)->GetPlayerFPVPlayerSkeletalMesh();
		FPVMesh->SetSkeletalMesh(FPVSkeletalMesh);

		// ABP 선택
		//UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerAnimInstance());
		UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(UIToSelectCharacter)->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}

	Super::PostInitializeComponents();

	// 리로드 위젯
	if (nullptr != Reload_Widget)
	{
		Reload_Widget->AddToViewport();
		Reload_Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	NetCheck();
	Super::BeginPlay();

	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);

	// PlayerState 초기화
	SettingPlayerState();

	PlayerAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	FPVPlayerAnimInst = Cast<UPlayerAnimInstance>(FPVMesh->GetAnimInstance());

	// GetMapItemCollision Component에 대한 함수 Bind
	GetMapItemCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATestCharacter::MapItemOverlapStart);
	GetMapItemCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATestCharacter::MapItemOverlapEnd);

	ChangeMontage(EPlayerUpperState::UArm_Idle);
}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 하체 정보
	DOREPLIFETIME(ATestCharacter, LowerStateValue);
	// 플레이어 자세 유형.
	DOREPLIFETIME(ATestCharacter, DirValue);
	DOREPLIFETIME(ATestCharacter, IdleDefault);

	DOREPLIFETIME(ATestCharacter, Token);
	//DOREPLIFETIME(ATestCharacter, IsFaint);

	DOREPLIFETIME(ATestCharacter, UIToSelectCharacter); // Test
}

void ATestCharacter::AnimationEnd()
{
	PlayerAnimInst->ChangeAnimation(IdleDefault);
	FPVPlayerAnimInst->ChangeAnimation(IdleDefault);
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerHp(DeltaTime);
}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestCharacter::ChangeLowerState_Implementation(EPlayerLowerState _LowerState)
{
	LowerStateValue = _LowerState;
}

void ATestCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir)
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

	DirValue = _Dir;
}

void ATestCharacter::DestroyItem_Implementation(AItemBase* _Item)
{
	// 필드에서 얻은 아이템 Destroy
	_Item->Destroy();
}

void ATestCharacter::SetItemSocketVisibility_Implementation(bool _Visibility)
{
	ItemSocketMesh->SetVisibility(_Visibility);
	FPVItemSocketMesh->SetVisibility(_Visibility);
}

void ATestCharacter::SetItemSocketMesh_Implementation(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale)
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

void ATestCharacter::SettingItemSocket(int _InputKey)
{
	if (-1 == _InputKey)
	{
		// ItemSocket의 Visibility 끄기
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

void ATestCharacter::SpawnItem_Implementation(FName _ItemName, FTransform _SpawnTrans)
{
	// 스폰할 아이템 정보 가져오기
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	const FItemDataRow* ItemData = MainGameInst->GetItemData(_ItemName);

	// 필드에 아이템 Spawn
	AItemBase* DropItem = GetWorld()->SpawnActor<AItemBase>(ItemData->GetItemUClass(), _SpawnTrans);
	UStaticMeshComponent* DropItemMeshComp = Cast<AItemBase>(DropItem)->GetStaticMeshComponent();
	DropItemMeshComp->SetSimulatePhysics(true);
}

void ATestCharacter::PickUpItem(AItemBase* _Item)
{
	const FItemDataRow* ItemData = _Item->GetItemData();
	EItemType ItemType = ItemData->GetItemType();
	int ItemSlotIndex = static_cast<int>(ItemType);
	FName ItemName = *(ItemData->GetName());

	// 이미 같은 이름을 가진 아이템이 인벤토리에 있을 경우 return
	if (ItemName == ItemSlot[ItemSlotIndex].Name)
	{
		return;
	}

	// 이미 같은 타입의 아이템이 인벤토리에 있을 경우 가지고 있던 아이템을 Drop
	if (true == ItemSlot[ItemSlotIndex].IsItemIn)
	{
		//DropItem(ItemSlotIndex);
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

	// 필드에 존재하는 아이템 액터 삭제
	DestroyItem(_Item);

	// Change 애니메이션
	{
		if (ItemType == EItemType::Rifle)
		{
			IdleDefault = EPlayerUpperState::Rifle_Idle;
			SettingItemSocket(static_cast<int>(ItemType));
			ChangeMontage(IdleDefault, true);
		}
		else if (ItemType == EItemType::Melee)
		{
			IdleDefault = EPlayerUpperState::Melee_Idle;
			SettingItemSocket(static_cast<int>(ItemType));
			ChangeMontage(IdleDefault, true);
		}
	}

	// To Controller -> To Widget
	//ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	//if (nullptr != Con)
	//{
	//	Con->FGetItemToWidget.Execute();
	//}
}

void ATestCharacter::DropItem(int _SlotIndex)
{
	CurItemIndex = 0;

	// DropItem 할 수 없는 경우 1: 맨손일 때
	if (CurItemIndex == -1)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (Current posture is 'Barehand')")));
#endif // WITH_EDITOR
		return;
	}

	// DropItem 할 수 없는 경우 2: (그럴리는 없겠지만) 현재 Posture에 해당하는 무기가 인벤토리에 없을 때
	if (false == ItemSlot[CurItemIndex].IsItemIn)
	{
#ifdef WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("There's no item to drop. (The item slot is empty)")));
#endif // WITH_EDITOR
		return;
	}

	// 떨어트릴 아이템을 Actor로 생성
	FName ItemName = ItemSlot[_SlotIndex].Name;
	FTransform SpawnTrans = GetActorTransform();
	SpawnTrans.SetTranslation(GetActorLocation() + (GetActorForwardVector() * 100.0f) + (GetActorUpVector() * 50.0f));

	SpawnItem(ItemName, SpawnTrans);


	// 자세를 맨손으로 변경
	ChangeMontage(IdleDefault);
}

void ATestCharacter::FireRayCast_Implementation()
{
	CurItemIndex = 0;
	if (CurItemIndex == -1 || CurItemIndex == 2)
	{
		return;
	}

	//// 탄알이 없다면 
	//if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	//{
	//	//ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	//	// 장전하라는 Widget을 띄워야 함.
	//	// 장전 함수는 CharacterReload 이다.
	//	Reload_Widget->SetVisibility(ESlateVisibility::Visible);
	//	return;
	//}

	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	FVector Start = GetMesh()->GetSocketLocation(FName("MuzzleSocket"));
	//Start.Z -= 20.0f;
	FVector End = (Con->GetControlRotation().Vector() * 2000.0f) + Start;

	FHitResult Hit;
	if (GetWorld())
	{
		// 탄수 깎기.
		ItemSlot[CurItemIndex].ReloadLeftNum -= 1;

		// Ray Cast
		TArray<AActor*> IgnoreActors; // 무시할 Actor들.
		bool ActorHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);

		DrawDebugLine(GetWorld(), Start, End, FColor::Red);

		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			FString BoneName = Hit.BoneName.ToString();
			ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(Hit.GetActor());
			if (nullptr != Monster)
			{
				Monster->Damaged(RifleDamage);
				return;
			}

			ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(Hit.GetActor());
			if (nullptr != BossMonster)
			{
				BossMonster->Damaged(RifleDamage);
				return;
			}

			AKrakenProjectile* Kraken = Cast<AKrakenProjectile>(Hit.GetActor());
			if (nullptr != Kraken)
			{
				Kraken->Damaged(RifleDamage);
				return;
			}
		}
	}
}

void ATestCharacter::ChangeMontage_Implementation(EPlayerUpperState _UpperState, bool IsSet)
{
	if (true == IsSet)
	{
		IdleDefault = _UpperState;
	}

	PlayerAnimInst->ChangeAnimation(_UpperState);
	FPVPlayerAnimInst->ChangeAnimation(_UpperState);
	ClientChangeMontage(_UpperState);
}

void ATestCharacter::ClientChangeMontage_Implementation(EPlayerUpperState _UpperState)
{
	PlayerAnimInst->ChangeAnimation(_UpperState);
	FPVPlayerAnimInst->ChangeAnimation(_UpperState);
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

void ATestCharacter::CrouchCameraMove()
{
	if (PointOfView == EPlayerFPSTPSState::FPS)
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
	else if (PointOfView == EPlayerFPSTPSState::TPS)
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

void ATestCharacter::MapItemOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetMapItemData = OtherActor;

	ATestPlayerController* MyController = Cast<ATestPlayerController>(GetController());
	if (nullptr == MyController)
	{
		return;
	}

	AMainGameHUD* PlayHUD = Cast<AMainGameHUD>(MyController->GetHUD());
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

void ATestCharacter::MapItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (nullptr != GetMapItemData)
	{
		GetMapItemData = nullptr;
	}

	ATestPlayerController* MyController = Cast<ATestPlayerController>(GetController());
	if (nullptr == MyController)
	{
		return;
	}

	AMainGameHUD* PlayHUD = Cast<AMainGameHUD>(MyController->GetHUD());
	if (nullptr == PlayHUD)
	{
		return;
	}

	// 켜져 있는 상호작용 관련 UI 모두 끄기
	PlayHUD->UIOff(EUserWidgetType::Num5_Key);
	PlayHUD->UIOff(EUserWidgetType::E_Key);
}

void ATestCharacter::UpdatePlayerHp(float _DeltaTime)
{
	ATestPlayerState* MyMainPlayerState = GetPlayerState<ATestPlayerState>();
	if (nullptr == MyMainPlayerState)
	{
		return;
	}

	ATestPlayerController* MyController = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (nullptr == MyController)
	{
		return;
	}

	float GetHp = MyMainPlayerState->GetPlayerHp();

	// Get HUD
	AMainGameHUD* PlayHUD = Cast<AMainGameHUD>(MyController->GetHUD());
	if (nullptr != PlayHUD)
	{
		FString Number = FString::FromInt(Token);
		FString Name_Number = FString("Play_") + Number;
		UTestHpBarUserWidget* MyHpWidget = Cast<UTestHpBarUserWidget>(PlayHUD->GetWidget(EUserWidgetType::HpBar));
		MyHpWidget->NickNameUpdate(Token, FText::FromString(Name_Number));
		MyHpWidget->HpbarUpdate(Token, GetHp, 100.0f);
	}
}

void ATestCharacter::CheckItem()
{
	// 맵에 아이템이 없을 경우.
	if (nullptr == GetMapItemData)
	{
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
		if (nullptr != GetMapItem)
		{
			PickUpItem(GetMapItem);
		}
	}
}

void ATestCharacter::AttackCheck()
{
	switch (IdleDefault)
	{
	case EPlayerUpperState::UArm_Idle:
		ChangeMontage(EPlayerUpperState::UArm_Attack);
		break;
	case EPlayerUpperState::Rifle_Idle:
		ChangeMontage(EPlayerUpperState::Rifle_Attack);
		FireRayCast();
		break;
	case EPlayerUpperState::Melee_Idle:
		ChangeMontage(EPlayerUpperState::Melee_Attack);
		break;
	default:
		break;
	}
}

void ATestCharacter::Drink()
{
	// 음료 체크
	if (false == IsItemInItemSlot(static_cast<int>(EItemType::Drink)))
	{
		return;
	}

	// 음료가 있음!
	SettingItemSocket(static_cast<int>(EItemType::Drink));

	// 애니메이션 실행.
	ChangeMontage(EPlayerUpperState::Drink);
}

void ATestCharacter::DeleteItem(int _Index)
{
	FPlayerItemInformation NewSlot;
	ItemSlot[_Index] = NewSlot;
	IsItemIn[_Index] = false;
}

void ATestCharacter::ChangeIsFaint_Implementation()
{
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());

	if (true == IsFaint)
	{
		IsFaint = false;
		if (nullptr != Con)
		{
			Con->FCharacterToFaint.Execute(IsFaint); // Execute -> Delegate 실행.
			this->bUseControllerRotationYaw = true;
		}
	}
	else
	{
		IsFaint = true;
		if (nullptr != Con)
		{
			Con->FCharacterToFaint.Execute(IsFaint); // Execute -> Delegate 실행.
			this->bUseControllerRotationYaw = false;
		}
	}
}

void ATestCharacter::InteractObject_Implementation(AMapObjectBase* _MapObject)
{
	// Door일 경우 : 상호작용은 Switch가 발동시키므로 return
	ADoorObject* DoorObject = Cast<ADoorObject>(_MapObject);
	if (nullptr != DoorObject)
	{
		return;
	}

	// Area일 경우 : 상호작용은 플레이어쪽에서 처리해야 하므로 return
	AAreaObject* AreaObject = Cast<AAreaObject>(_MapObject);
	if (nullptr != AreaObject)
	{
		return;
	}

	// 그 외 맵오브젝트(Switch 등)일 경우 : 상호작용 발동
	_MapObject->InterAction();
}

void ATestCharacter::BombSetStart_Implementation()
{
	// 폭탄 아이템 체크
	if (false == ItemSlot[static_cast<int>(EItemType::Bomb)].IsItemIn)
	{
		return;
	}

	// 폭탄 설치 가능한 Area 체크
	AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);
	if (nullptr == AreaObject)
	{
		return;
	}

	// 폭탄 설치 가능.
	IsBombSetting = true;
	AreaObject->ResetBombTime();
	ChangeMontage(EPlayerUpperState::Bomb);
}

void ATestCharacter::BombSetTick_Implementation()
{
	if (true == IsBombSetting)
	{
		// 폭탄 설치 가능한 Area 체크
		AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);
		if (nullptr == AreaObject)
		{
			return;
		}

		// 설치 시간 카운트가 끝났을 경우
		if (0 >= AreaObject->GetInstallBombTime())
		{
			BombSetEnd();
		}

		// 설치 시간 카운팅
		AreaObject->InstallBomb(GetWorld()->GetDeltaSeconds());
	}
}

void ATestCharacter::BombSetCancel_Implementation()
{
	if (true == IsBombSetting)
	{
		IsBombSetting = false;
		AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);
		if (nullptr != AreaObject)
		{
			AreaObject->ResetBombTime();
		}

		// 이전 자세로 애니메이션 변경
		ChangeMontage(IdleDefault);
	}
}

void ATestCharacter::BombSetEnd_Implementation()
{
	if (true == IsBombSetting)
	{
		// 폭탄 설치 완료
		IsBombSetting = false;

		AAreaObject* AreaObject = Cast<AAreaObject>(GetMapItemData);
		if (nullptr != AreaObject)
		{
			AreaObject->InterAction();
		}

		// 인벤토리에서 폭탄 아이템 삭제
		DeleteItemInfo(static_cast<int>(EItemType::Bomb));

		// 이전 자세로 애니메이션 변경
		ChangeMontage(IdleDefault);
	}
}

void ATestCharacter::GetSetSelectCharacter_Implementation(UMainGameInstance* _MainGameInstance)
{
	UIToSelectCharacter = _MainGameInstance->GetUIToSelectCharacter();
}

void ATestCharacter::DeleteItemInfo(int _Index)
{
	FPlayerItemInformation DeleteSlot;
	ItemSlot[_Index] = DeleteSlot;
}

bool ATestCharacter::IsItemInItemSlot(int _Index)
{
	return ItemSlot[_Index].IsItemIn;
}

void ATestCharacter::ChangePOV()
{
	if (PointOfView == EPlayerFPSTPSState::FPS)
	{
		// SpringArm 위치 수정
		SpringArmComponent->TargetArmLength = 300.0f;
		SpringArmComponent->SetRelativeLocation(CameraRelLoc);

		// Character Mesh 전환
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);

		// Item Mesh
		for (int i = 0; i < static_cast<int>(EPlayerUpperState::UArm_Attack); i++)
		{
			ItemSocketMesh->SetOwnerNoSee(false);
			FPVItemSocketMesh->SetOwnerNoSee(true);
		}

		// 일인칭 -> 삼인칭
		PointOfView = EPlayerFPSTPSState::TPS;
	}
	else if (PointOfView == EPlayerFPSTPSState::TPS)
	{
		// SpringArm 위치 수정
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

		// 삼인칭 -> 일인칭
		PointOfView = EPlayerFPSTPSState::FPS;
	}
}

void ATestCharacter::CharacterReload()
{
	if (-1 == CurItemIndex)
	{
		return;
	}

	// Widget 숨기기
	Reload_Widget->SetVisibility(ESlateVisibility::Hidden);

	// 총알 데이터 설정.
	ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;

	// 변경된 총알 데이터 호출.
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	if (nullptr != Con)
	{
		Con->FCharacterToReload.Execute(); // Execute -> Delegate 실행.
	}
}

void ATestCharacter::HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	{
		ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(_OtherActor);
		if (nullptr != Monster)
		{
			Monster->Damaged(50.0f);
		}
	}

	{
		ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(_OtherActor); // 추후 Main으로 바꿔야 함.
		if (nullptr != BossMonster)
		{
			BossMonster->Damaged(50.0f);
		}
	}

	{
		AKrakenProjectile* Rock = Cast<AKrakenProjectile>(_OtherActor);
		if (nullptr != Rock)
		{
			Rock->Damaged(150.0f);
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
		if (nullptr == Inst)
		{
			return;
		}
		// 이토큰은 그 인덱스가 아니다.
		Token = Inst->GetNetToken();
	}
}

void ATestCharacter::SendTokenToHpBarWidget()
{
	ATestPlayerController* Con = Cast<ATestPlayerController>(GetController());
	if (nullptr == Con)
	{
		return;
	}

	AMainGameHUD* PlayHUD = Cast<AMainGameHUD>(Con->GetHUD());
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
}

TArray<struct FPlayerItemInformation> ATestCharacter::GetItemSlot()
{
	return ItemSlot;
}
