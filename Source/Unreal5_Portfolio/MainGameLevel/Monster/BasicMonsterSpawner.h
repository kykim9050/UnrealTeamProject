// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicMonsterSpawner.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasicMonsterSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnBasicMonster();
	
private:
	// Spawn Monster UClass
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TArray<TSubclassOf<AActor>> MonsterUClass;

	// Total Number of Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int TotalSpawnCount = 0;

	// Time interval between Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float SpawnDelayTime = 0.0f;

	// Number of creation per time
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int SpawnMonsterCount = 0;
	
	// Max Spawn Radius
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float MaxSpawnRadius = 0.0f;

	UPROPERTY()
	float TimeCount = 0.0f;

};
