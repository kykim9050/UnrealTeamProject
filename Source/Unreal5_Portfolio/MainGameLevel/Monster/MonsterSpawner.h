// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/DataTable/MonsterSpawnerDataRow.h"
#include "Global/ContentsEnum.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void InitSpawner(EMonsterSpawnerType _Type, const FVector& _Location, float _Radius, int _MinSize, int _MaxSize);

	UFUNCTION(Reliable, Server)
	void SpawnMonster();
	void SpawnMonster_Implementation();

private:
	UPROPERTY()
	UMonsterSpawnerData* SettingData = nullptr;

};
