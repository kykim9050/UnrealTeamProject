// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	UWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttachWeapon(class ATestCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DetachWeapon();

	virtual void BeginPlay() override;

	ATestCharacter* Character;

};
