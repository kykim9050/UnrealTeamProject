// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"
#include "TestLevel/Monster/TestMonsterBase.h"

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
		ItemMeshes.Push(NewSocketMesh);

		// Inventory (for UI Test)
		FItemInfo NewSlot;
		NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;
		ItemSlot.Push(NewSlot);
		IsItemIn.Push(false);
	}

	// HandAttack Component
	FString Name = "Pist";
	HandAttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hand Attack Comp"));
	HandAttackComponent->SetupAttachment(GetMesh(), *Name);
	//HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));

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

	Monster->GetDamage(150.0f);
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

	HandAttackComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CreateRayCast(DeltaTime);
}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestCharacter, StateValue);
	DOREPLIFETIME(ATestCharacter, PostureValue);

	// 플레이어 H
	DOREPLIFETIME(ATestCharacter, PlayerHp);
}

void ATestCharacter::CreateRayCast(float _DeltaTime, FVector _StartPos, FVector _EndPos, FRotator _CameraRot)
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

FString ATestCharacter::GetRayCastToItemName() const
{
	return RayCastToItemName;
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

void ATestCharacter::PickUpItem_Implementation(FName _ItemName)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(_ItemName);

	EPlayerPosture ItemType = ItemData->GetType();
	UStaticMesh* ItemMesh = ItemData->GetResMesh();
	int ItemReloadNum = ItemData->GetReloadNum();

	uint8 ItemIndex = static_cast<uint8>(ItemType);

	// Setting Weapon Mesh
	ItemMeshes[ItemIndex]->SetStaticMesh(ItemMesh);
	GetMapItem->Destroy();
	
	// Setting Inventory
	ItemSlot[ItemIndex].Name = _ItemName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	IsItemIn[ItemIndex] = true;

	ChangePosture(ItemType);
}