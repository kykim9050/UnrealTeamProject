// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/ContentsEnum.h"
#include "BasicMonsterSpawner.generated.h"

class UBoxComponent;
class ABasicMonsterBase;

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
	TArray<TSubclassOf<ABasicMonsterBase>> MonsterUClass;

	// Total Number of Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int TotalSpawnCount = 0;

	// Init Spawn Delay Time
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float InitSpawnDelayTime = 0.0f;

	// Time interval between Spawn
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float SpawnDelayTime = 0.0f;

	// Number of creation per time
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int SpawnMonsterCount = 0;
	
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
