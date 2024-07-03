// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "RangedWPComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API URangedWPComponent : public UWeaponComponent
{
	GENERATED_BODY()

protected:
	URangedWPComponent();

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttachWeapon(class ATestCharacter* TargetCharacter) override;

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DetachWeapon() override;

	/** Ends gameplay for this component. */
	//UFUNCTION()
	//void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginPlay() override;
	
};
