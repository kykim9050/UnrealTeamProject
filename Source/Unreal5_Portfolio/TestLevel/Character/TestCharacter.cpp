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
	
	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 1; i < static_cast<size_t>(EPlayerPosture::SlotMax); i++)
	{
		// Weapon Meshes
		FString Name = Enum->GetNameStringByValue(i) + "Socket";
		UStaticMeshComponent* NewSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSocketMesh->SetupAttachment(GetMesh(), *Name);
		NewSocketMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewSocketMesh->SetGenerateOverlapEvents(true);
		NewSocketMesh->SetVisibility(false);
		ItemMeshes.Push(NewSocketMesh);

		// Item Slot (for UI Test)
		FItemInfo NewSlot;
		NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;
		ItemSlot.Push(NewSlot);
		IsItemIn.Push(false);
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

void ATestCharacter::CreateRayCast()
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
		
		for (size_t i = 1; i < static_cast<size_t>(EPlayerPosture::SlotMax); i++)
		{
			ItemMeshes[i - 1]->SetVisibility(false);
		}
	}
	else
	{
		int ItemSlotIndex = static_cast<int>(_Type) - 1;
		if (IsItemIn[ItemSlotIndex] == false)
		{
			return;
		}

		PostureValue = _Type;
		CurItemIndex = ItemSlotIndex;

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
}

void ATestCharacter::PickUpItem_Implementation(FName _ItemName)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(_ItemName);

	EPlayerPosture ItemType = ItemData->GetType();
	UStaticMesh* ItemMesh = ItemData->GetResMesh();
	int ItemReloadNum = ItemData->GetReloadNum();

	uint8 ItemIndex = static_cast<uint8>(ItemType) - 1;

	// Setting Weapon Mesh
	ItemMeshes[ItemIndex]->SetStaticMesh(ItemMesh);

	// Setting Item Info
	ItemSlot[ItemIndex].Name = _ItemName;
	ItemSlot[ItemIndex].ReloadMaxNum = ItemReloadNum;
	ItemSlot[ItemIndex].ReloadLeftNum = ItemReloadNum;
	IsItemIn[ItemIndex] = true;

	ChangePosture(ItemType);
}