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

	UFUNCTION()
	FORCEINLINE void SetSwitchValue(bool _Value)
	{
		SwitchValue = _Value;
	}

protected:
	ASwitchObject();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TSubclassOf<AMapObjectBase> InteractObjClass = TSubclassOf<AMapObjectBase>();

	UPROPERTY()
	bool SwitchValue = false;

};
