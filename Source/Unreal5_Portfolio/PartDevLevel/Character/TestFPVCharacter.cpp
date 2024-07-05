// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/TestFPVCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/ItemDataRow.h"

// Sets default values
ATestFPVCharacter::ATestFPVCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->bDoCollisionTest = false;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	CameraComponent->bUsePawnControlRotation = true;

	// Mesh
	GetMesh()->SetOwnerNoSee(true);

	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		// Item Meshes
		FString MeshName = Enum->GetNameStringByValue(i) + "Mesh";
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(*MeshName);
		NewMesh->SetupAttachment(GetMesh(), *MeshName);
		NewMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewMesh->SetGenerateOverlapEvents(true);
		NewMesh->SetOwnerNoSee(true);
		NewMesh->SetVisibility(false);
		ItemMeshes.Push(NewMesh);

		FString FPVMeshName = Enum->GetNameStringByValue(i) + "FPVMesh";
		UStaticMeshComponent* NewFPVMesh = CreateDefaultSubobject<UStaticMeshComponent>(*FPVMeshName);
		NewFPVMesh->SetupAttachment(FPVMesh, *FPVMeshName);
		NewFPVMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewFPVMesh->SetGenerateOverlapEvents(true);
		NewFPVMesh->SetOnlyOwnerSee(true);
		NewFPVMesh->bCastDynamicShadow = false;
		NewFPVMesh->CastShadow = false;
		NewFPVMesh->SetVisibility(false);
		FPVItemMeshes.Push(NewFPVMesh);

		// Inventory (for UI Test)
		FItemInfo NewSlot;
		NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;
		ItemSlot.Push(NewSlot);
		IsItemIn.Push(false);
	}
	int a = 0;
}

void ATestFPVCharacter::Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestFPVCharacter* OtherPlayCharacter = Cast<ATestFPVCharacter>(_OtherActor);
	if (nullptr == OtherPlayCharacter)
	{
		return;
	}

	int a = 0;
	// Collision_Check
	//if (true == _Collision->ComponentHasTag())
	//{}
}

void ATestFPVCharacter::GetDamage(float _Damage)
{
	PlayerHp -= _Damage;
}

// Called when the game starts or when spawned
void ATestFPVCharacter::BeginPlay()
{
	Super::BeginPlay();
	UMainGameBlueprintFunctionLibrary::PushActor(EObjectType::Player, this);
}

// Called every frame
void ATestFPVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestFPVCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestFPVCharacter, StateValue);
	DOREPLIFETIME(ATestFPVCharacter, PostureValue);
	DOREPLIFETIME(ATestFPVCharacter, PlayerHp);
	DOREPLIFETIME(ATestFPVCharacter, ItemMeshes);
	DOREPLIFETIME(ATestFPVCharacter, FPVItemMeshes);
}

void ATestFPVCharacter::CreateRayCast()
{
	FVector Start = GetActorLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();

	Start = FVector(Start.X + (ForwardVector.X * 100), Start.Y + (ForwardVector.Y * 100), Start.Z + (ForwardVector.Z * 100));

	FVector End = Start + (ForwardVector * 1000);

	FHitResult Hit;
	if (GetWorld())
	{
		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, FCollisionQueryParams(), FCollisionResponseParams());
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0.0f, 0.0f);

		if (true == ActorHit && Hit.GetActor())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, Hit.GetActor()->GetFName().ToString());
			//Hit.GetActor()->ActorHasTag(TEXT(""));
			AActor* GetActorTest = Hit.GetActor();
			int TagCount = Hit.GetActor()->Tags.Num();
			if (0 != TagCount)
			{
				for (size_t i = 0; i < Hit.GetActor()->Tags.Num(); i++)
				{
					FString TagName = Hit.GetActor()->Tags[i].ToString();
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TagName);
				}
			}
			int a = 0;
		}
	}
}

void ATestFPVCharacter::ChangeState_Implementation(EPlayerState _Type)
{
	StateValue = _Type;
}

void ATestFPVCharacter::ChangePosture_Implementation(EPlayerPosture _Type)
{
	if (_Type == EPlayerPosture::Barehand)
	{
		PostureValue = _Type;
		CurItemIndex = -1;

		for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
		{
			ItemMeshes[i]->SetVisibility(false);
			FPVItemMeshes[i]->SetVisibility(false);
		}
	}
	else
	{
		int ItemSlotIndex = static_cast<int>(_Type);
		/*if (IsItemIn[ItemSlotIndex] == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The item slot is empty."));
			return;
		}*/

		PostureValue = _Type;
		CurItemIndex = ItemSlotIndex;

		for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
		{
			if (i == static_cast<size_t>(_Type))
			{
				ItemMeshes[i]->SetVisibility(true);
				FPVItemMeshes[i]->SetVisibility(true);
			}
			else
			{
				ItemMeshes[i]->SetVisibility(false);
				FPVItemMeshes[i]->SetVisibility(false);
			}
		}
	}
}

void ATestFPVCharacter::PickUpItem_Implementation(FName _ItemName)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(_ItemName);

	EPlayerPosture ItemType = ItemData->GetType();
	UStaticMesh* ItemResMesh = ItemData->GetResMesh();
	int ItemReloadNum = ItemData->GetReloadNum();

	uint8 ItemIndex = static_cast<uint8>(ItemType);

	// Setting Weapon Mesh
	ItemMeshes[ItemIndex]->SetStaticMesh(ItemResMesh);
	FPVItemMeshes[ItemIndex]->SetStaticMesh(ItemResMesh);

	// Setting Inventory
	ItemSlot[ItemIndex].Name = _ItemName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	IsItemIn[ItemIndex] = true;

	ChangePosture(ItemType);
}