// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/WeaponComponent.h"
#include "Global/MainGameInstance.h"
#include "TestLevel/Character/TestCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UWeaponComponent::UWeaponComponent()
{

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//UMainGameInstance* Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();

	//if (nullptr == Inst)
	//{
	//	UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == Inst)"), __FUNCTION__, __LINE__);
	//}

	//UInputDatas* Asset = Inst->GetInputDataAsset();
	//FireMappingContext = Asset->GetInputMapping();

	//FireAction = *(Asset->GetActions().Find(TEXT("Shoot")));
	//DetachAction = *(Asset->GetActions().Find(TEXT("Detach")));

	//UStaticMesh* Mesh = Inst->GetStaticMeshData(TEXT("Rifle_Mesh"));
	//SetStaticMesh(Mesh);
}

void UWeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	IsFire = true;
}

void UWeaponComponent::FireEnd()
{
	IsFire = false;
}

void UWeaponComponent::DetachWeapon()
{
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);

	DetachFromComponent(DetachmentRules);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			FireMappingContext = nullptr;
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->ClearBindingsForObject(this);

			FireAction = nullptr;
			DetachAction = nullptr;
		}
	}

	Character->RemoveInstanceComponent(this);
}

bool UWeaponComponent::AttachWeapon(ATestCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UWeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	FName AttachSocket = Character->GetMesh()->GetSocketBoneName(FName(TEXT("RifleSocket")));
	AttachToComponent(Character->GetMesh(), AttachmentRules, AttachSocket);


	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Fire);

			// Fire End
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UWeaponComponent::FireEnd);

			EnhancedInputComponent->BindAction(DetachAction, ETriggerEvent::Started, this, &UWeaponComponent::DetachWeapon);
		}
	}

	return true;
}

//void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	if (Character == nullptr)
//	{
//		return;
//	}
//
//	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
//	{
//		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//		{
//			Subsystem->RemoveMappingContext(FireMappingContext);
//		}
//	}
//}