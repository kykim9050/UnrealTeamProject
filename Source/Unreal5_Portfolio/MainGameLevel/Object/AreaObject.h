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

	FORCEINLINE void ResetBombTime()
	{
		InstallBombTime = 3.0f;
	}

	FORCEINLINE float GetInstallBombTime() const
	{
		return InstallBombTime;
	}

	void InstallBomb(float _DeltaTime);

protected:
	AAreaObject();
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	UFUNCTION(Reliable, NetMulticast)
	void BombPlanting(FName _InfoName);
	void BombPlanting_Implementation(FName _InfoName);

private:
	/// <summary>
	/// ÆøÅº ¼³Ä¡ ½Ã°£
	/// </summary>
	float InstallBombTime = 3.0f;



	class UStaticMeshComponent* BombMesh = nullptr;
	class UBoxComponent* PlantingSpotCollision = nullptr;

};
