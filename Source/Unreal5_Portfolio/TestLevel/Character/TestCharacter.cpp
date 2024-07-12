// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->bDoCollisionTest = false;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	CameraComponent->bUsePawnControlRotation = true;

	// MinimapIcon Component
	MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	MinimapIconComponent->SetupAttachment(RootComponent);
	MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// Mesh
	GetMesh()->bHiddenInSceneCapture = true;

	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		// Weapon Meshes
		FString Name = Enum->GetNameStringByValue(i) + "Socket";
		UStaticMeshComponent* NewSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSocketMesh->SetupAttachment(GetMesh(), *Name);
		NewSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewSocketMesh->SetGenerateOverlapEvents(true);
		NewSocketMesh->SetVisibility(false);
		NewSocketMesh->SetIsReplicated(true);
		ItemMeshes.Push(NewSocketMesh);

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
	//UAnimInstance* Inst = GetMesh()->GetAnimInstance();
	//AnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DefaultRayCast(DeltaTime);

	TArray<FItemInformation> I = ItemSlot;
	AGameModeBase* Ptr = GetWorld()->GetAuthGameMode();

	// 몽타주 Tick에서 실행 (태환)
	//AnimInst->ChangeAnimation(AniValue);
}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestCharacter, StateValue);
	DOREPLIFETIME(ATestCharacter, PostureValue);
	DOREPLIFETIME(ATestCharacter, RayCastToItemName);

	// 플레이어 H
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

void ATestCharacter::FireRayCast_Implementation(float _DeltaTime)
{
	if (CurItemIndex == -1 || ItemSlot[CurItemIndex].ReloadMaxNum == -1)
	{
		return;
	}

	if (ItemSlot[CurItemIndex].ReloadLeftNum <= 0)
	{
		ItemSlot[CurItemIndex].ReloadLeftNum = ItemSlot[CurItemIndex].ReloadMaxNum;
	}

	FVector Start = GetActorLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));
	FVector End = Start + (ForwardVector * 1000.0);

	FHitResult Hit;
	if (GetWorld())
	{
		ItemSlot[CurItemIndex].ReloadLeftNum -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Bullet left : %d / %d"), ItemSlot[CurItemIndex].ReloadLeftNum, ItemSlot[CurItemIndex].ReloadMaxNum));

		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel2, FCollisionQueryParams(), FCollisionResponseParams());
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, _DeltaTime, 0.0f, 0.0f);

		if (true == ActorHit && nullptr != Hit.GetActor())
		{
			ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Hit.GetActor());
			if (nullptr != Monster)
			{
				Monster->Damaged(50.0f);
			}
		}
	}
}

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

		for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
		{
			ItemMeshes[i]->SetVisibility(false);
		}
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

		for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
		{
			if (i == static_cast<size_t>(_Type))
			{
				ItemMeshes[i]->SetVisibility(true);
			}
			else
			{
				ItemMeshes[i]->SetVisibility(false);
			}
		}
	}
}

void ATestCharacter::ChangeLowerState_Implementation(EPlayerLowerState _State)
{
	LowerStateValue = _State;
}

void ATestCharacter::ChangePlayerDir_Implementation(EPlayerMoveDir _Dir)
{
	DirValue = _Dir;
}

void ATestCharacter::ChangeAniValue(uint8 _Type)
{
	AniValue = _Type;
}

void ATestCharacter::PickUpItem_Implementation()
{
	//AGameModeBase* Test = GetWorld()->GetAuthGameMode();
	//ATestPlayerController* PlayerControl = Cast<ATestPlayerController>(GetController());
	// 
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
	UStaticMesh* ItemMesh = ItemData->GetResMesh(); // Static Mesh
	int ItemReloadNum = ItemData->GetReloadNum();	// 장전 단위.(30, 40)

	uint8 ItemIndex = static_cast<uint8>(ItemType); // 사용할 소켓 번호.

	// Setting Weapon Mesh
	ItemMeshes[ItemIndex]->SetStaticMesh(ItemMesh); // Static Mesh 적용.
	GetMapItem->Destroy(); // Map에 있는 아이템 삭제.

	// Setting Inventory
	ItemSlot[ItemIndex].Name = ItemStringToName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	IsItemIn[ItemIndex] = true;

	ChangePosture(ItemType); // 무기 Type에 따른 애니메이션 변화 함수 호출.
}