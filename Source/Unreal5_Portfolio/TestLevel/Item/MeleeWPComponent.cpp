// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/MeleeWPComponent.h"
#include "Global/MainGameInstance.h"
#include "TestLevel/Character/TestCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UMeleeWPComponent::UMeleeWPComponent()
{
}

void UMeleeWPComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMeleeWPComponent::DetachWeapon()
{
	Super::DetachWeapon();
}

void UMeleeWPComponent::AttachWeapon(ATestCharacter* TargetCharacter)
{
	Super::AttachWeapon(TargetCharacter);

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	FName AttachSocket = Character->GetMesh()->GetSocketBoneName(FName(TEXT("MeleeSocket")));
	AttachToComponent(Character->GetMesh(), AttachmentRules, AttachSocket);
}

