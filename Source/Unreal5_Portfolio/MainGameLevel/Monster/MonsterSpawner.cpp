// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/MonsterSpawner.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::InitSpawner(EMonsterSpawnerType _Type, const FVector& _Location, int _MinSize, int _MaxSize)
{
	SetActorLocation(_Location);

	SettingData = NewObject<UMonsterSpawnerData>(this);
	SettingData->MinSize = _MinSize;
	SettingData->MaxSize = _MaxSize;	
}

