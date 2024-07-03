// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"

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

	// Weapon Meshes
	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 1; i < static_cast<size_t>(EPlayerPosture::SlotMax); i++)
	{
		FString Name = Enum->GetNameStringByValue(i) + "Socket";
		UStaticMeshComponent* NewSlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSlotMesh->SetupAttachment(GetMesh(), *Name);
		NewSlotMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewSlotMesh->SetGenerateOverlapEvents(true);
		NewSlotMesh->SetVisibility(false);
		ItemMeshes.Push(NewSlotMesh);
	}
}

void ATestCharacter::Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestCharacter* OtherPlayCharacter = Cast<ATestCharacter>(_OtherActor);
	if (nullptr == OtherPlayCharacter)
	{
		return;
	}

	int a = 0;
	// Collision_Check
	//if (true == _Collision->ComponentHasTag())
	//{}
}

float ATestCharacter::GetPlayerHp()
{
	return PlayerHp;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestCharacter, StateValue);
	DOREPLIFETIME(ATestCharacter, PostureValue);
}

void ATestCharacter::ChangeState_Implementation(EPlayerState _Type)
{
	StateValue = _Type;
}

void ATestCharacter::ChangePosture_Implementation(EPlayerPosture _Type)
{
	PostureValue = _Type;

	for (size_t i = 1; i < static_cast<size_t>(EPlayerPosture::SlotMax); i++)
	{
		if (i == static_cast<size_t>(_Type))
		{
			ItemMeshes[i - 1]->SetVisibility(true);
		}
		else
		{
			ItemMeshes[i - 1]->SetVisibility(false);
		}
	}
}

void ATestCharacter::GetItem_Implementation(FName _ItemName)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(_ItemName);

	EPlayerPosture ItemType = ItemData->GetType();
	UStaticMesh* ItemMesh = ItemData->GetResMesh();

	ItemMeshes[static_cast<uint8>(ItemType) - 1]->SetStaticMesh(ItemMesh);

	ChangePosture(ItemType);
}