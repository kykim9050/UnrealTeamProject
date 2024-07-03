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
}

void UWeaponComponent::DetachWeapon()
{
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);

	DetachFromComponent(DetachmentRules);

	// Character->RemoveInstanceComponent(this);
}

void UWeaponComponent::AttachWeapon(ATestCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UWeaponComponent>())
	{
		return;
	}

	// add the weapon as an instance component to the character
	// Character->AddInstanceComponent(this);

}
