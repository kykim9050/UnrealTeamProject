// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "RangedWPComponent.generated.h"

/**
 * 원거리 무기 컴포넌트
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API URangedWPComponent : public UWeaponComponent
{
	GENERATED_BODY()

protected:
	URangedWPComponent();

	virtual void AttachWeapon(class ATestCharacter* TargetCharacter) override;

	virtual void DetachWeapon() override;

	/** Ends gameplay for this component. */
	//UFUNCTION()
	//void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginPlay() override;
	
};
