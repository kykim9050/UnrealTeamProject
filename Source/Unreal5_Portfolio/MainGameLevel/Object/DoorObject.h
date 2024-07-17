// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "DoorObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ADoorObject : public AMapObjectBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMesh(FName _ObjName);

protected:
	ADoorObject();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:

};
