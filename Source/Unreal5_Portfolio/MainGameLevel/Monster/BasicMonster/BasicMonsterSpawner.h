// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/ContentsEnum.h"
#include "BasicMonsterSpawner.generated.h"

class UBoxComponent;
class ABasicMonsterBase;

USTRUCT()
struct FFixedSpawn
{
	GENERATED_BODY()

public:
	// Spawn Monster UClass
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicMonsterBase> MonsterUClass;
	
	// Number of creation per time (Fixed)
	UPROPERTY(EditAnywhere)
	int SpawnFixedMonsterCount = 0;

};

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
	TArray<TSubclassOf<ABasicMonsterBase>> RandomMonsterUClass;

	// Number of creation per time (Random)
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int SpawnRandomMonsterCount = 0;

	// Fixed Spawn Type
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TArray<FFixedSpawn> FixedSpawn;

	// Total Number of Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int TotalSpawnCount = 0;

	// Init Spawn Delay Time
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float InitSpawnDelayTime = 0.0f;

	// Time interval between Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float SpawnDelayTime = 0.0f;
	
	// Max Spawn Radius
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float MaxSpawnRadius = 0.0f;
	
	// Chasing Player When Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	bool IsChasePlayer = false;

	UPROPERTY()
	float TimeCount = 0.0f;

private:
	UFUNCTION()
	void TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// Spawn TriggerBox
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	UBoxComponent* TriggerBox = nullptr;
	
	// TriggerBox Stage
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	EGameStage TriggerCheckStage = EGameStage::Max;

	// TriggerBox is Active
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	bool TriggerIsActive = false;

};
