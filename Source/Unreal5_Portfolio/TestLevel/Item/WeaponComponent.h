// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * ¹«±â È¹µæ ¹× ¹ö¸®´Â ±â´É ºÎ¸ð ÄÄÆ÷³ÍÆ®
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	//¹«±â È¹µæ
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttachWeapon(class ATestCharacter* TargetCharacter);

	//¹«±â ¹ö¸®±â
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DetachWeapon();

protected:
	virtual void BeginPlay() override;

	ATestCharacter* Character;

};
