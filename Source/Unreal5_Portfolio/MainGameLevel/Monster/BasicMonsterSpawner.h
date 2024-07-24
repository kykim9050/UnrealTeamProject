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

	// Total Spawn Num
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int SpawnCount = 0;

	// Spawn CoolTime
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float SpawnDelayTime = 0;

	// Once Spawn Monster Count
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	int SpawnMonsterCount = 0;
	
	UPROPERTY()
	float TimeCount = 0.0f;

};
