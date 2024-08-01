// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "AreaObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AAreaObject : public AMapObjectBase
{
	GENERATED_BODY()

public:
	void InterAction() override;

protected:
	AAreaObject();
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	void BombPlanting(FName _InfoName);

private:
	float BombInstallTime = 3.0f;

	class UStaticMeshComponent* BombMesh = nullptr;
	class UBoxComponent* PlantingSpotCollision = nullptr;

};
