// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/RangedWPComponent.h"
#include "Global/MainGameInstance.h"
#include "TestLevel/Character/TestCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

URangedWPComponent::URangedWPComponent()
{
}

void URangedWPComponent::BeginPlay()
{
	Super::BeginPlay();

}

void URangedWPComponent::DetachWeapon()
{
	Super::DetachWeapon();
}

void URangedWPComponent::AttachWeapon(ATestCharacter* TargetCharacter)
{
	Super::AttachWeapon(TargetCharacter);
}