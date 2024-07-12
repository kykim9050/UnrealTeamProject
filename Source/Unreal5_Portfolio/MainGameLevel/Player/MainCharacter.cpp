// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"


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
	SpringArmComponent->bDoCollisionTest = false;

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	// Character Mesh
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bHiddenInSceneCapture = true;

	// FPV Character Mesh
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPVMesh->SetupAttachment(CameraComponent);
	FPVMesh->SetOnlyOwnerSee(true);
	FPVMesh->bCastDynamicShadow = false;
	FPVMesh->CastShadow = false;

	// MinimapIcon Component
	//MinimapIconComponent = CreateDefaultSubobject<UTestMinimapIconComponent>(TEXT("MinimapPlayerIcon"));
	//MinimapIconComponent->SetupAttachment(RootComponent);
	//MinimapIconComponent->bVisibleInSceneCaptureOnly = true;

	// Item Create Component
	CreateItemComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CreateItemComponent"));
	CreateItemComponent->SetupAttachment(RootComponent);
	CreateItemComponent->SetRelativeLocation(FVector(100.0, 0.0, -90.0));

	// Map Item 
	GetMapItemCollisonComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("GetMapItemCollisionComponent"));
	GetMapItemCollisonComponent->SetupAttachment(RootComponent);
	GetMapItemCollisonComponent->SetRelativeLocation(FVector(100.0, 0.0, -70.0f));
	GetMapItemCollisonComponent->SetCollisionProfileName(FName("MapItemSearch"));

	// Inventory
	UEnum* Enum = StaticEnum<EPlayerPosture>();
	for (size_t i = 0; i < static_cast<size_t>(EPlayerPosture::Barehand); i++)
	{
		/*
		FItemInformation NewSlot;
		NewSlot.Name = "";
		NewSlot.ReloadMaxNum = -1;
		NewSlot.ReloadLeftNum = -1;
		ItemSlot.Push(NewSlot);
		IsItemIn.Push(false);
		*/
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::PickUpItem_Implementation()
{
	// 아이템이 없을 경우.
	if (nullptr == GetMapItemData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Not Item"));
		return;
	}

	// 아이템이 있다면 해당 아이템의 Tag를 가져온다.
	FString TagName = "";
	for (size_t i = 0; i < GetMapItemData->Tags.Num(); i++)
	{
		TagName = GetMapItemData->Tags[i].ToString();
	}

	FName ItemName = FName(*TagName);

	// 손에 아이템이 있다면,
	// 소켓에 있는 것을 지워주고,
	


	// Map에 아이템 생성.
	// FTransform CreatePos = GetMapItemCollisonComponent->GetComponentToWorld(); // 체크 필요.
	// CharacterPlayerToDropItem(ItemName, CreatePos);

	
	// 손에 아이템을 생성한다.
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	const FItemDataRow* ItemData = Inst->GetItemData(ItemName);


	// 주은 무기 삭제.
	// GetMapItemData->Destroy();
}

void AMainCharacter::CharacterPlayerToDropItem_Implementation(FName _ItemName, FTransform _Transform)
{
	// 무기를 장착 했을 때,

	FName CreateItemName = "";



	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FItemDataRow* ItemBase = MainGameInst->GetItemData(CreateItemName);
	GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), _Transform);
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

void AMainCharacter::ChangePOV()
{
	if (IsFPV)
	{
		// SpringArm 위치 수정
		SpringArmComponent->TargetArmLength = 200.0f;
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

		// Character Mesh 전환
		GetMesh()->SetOnlyOwnerSee(true);
		GetMesh()->SetOwnerNoSee(false);
		FPVMesh->SetOwnerNoSee(true);
		FPVMesh->SetOnlyOwnerSee(false);

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
		GetMesh()->SetOnlyOwnerSee(false);
		FPVMesh->SetOnlyOwnerSee(true);
		FPVMesh->SetOwnerNoSee(false);

		// 삼인칭 -> 일인칭
		IsFPV = true;
	}
}