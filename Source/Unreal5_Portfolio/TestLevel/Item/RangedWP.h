// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestLevel/Item/WeaponBase.h"
#include "RangedWP.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ARangedWP : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARangedWP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
