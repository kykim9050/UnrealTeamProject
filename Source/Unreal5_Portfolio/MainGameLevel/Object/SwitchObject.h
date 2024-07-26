// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "SwitchObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ASwitchObject : public AMapObjectBase
{
	GENERATED_BODY()
	
public:



protected:
	ASwitchObject();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	void InterAction() override;


private:

	UPROPERTY()
	FVector CollisionOffset = FVector(0.0f, 60.0f, 0.0f);
};
