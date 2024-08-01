// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Kraken/SpawnRock_Points.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

// Sets default values for this component's properties
USpawnRock_Points::USpawnRock_Points()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SpawnPos.SetNum(5);
	for (int i = 0; i < SpawnPos.Num(); i++)
	{
		SpawnPos[i] = FVector::ZeroVector;
	}
}

// Called when the game starts
void USpawnRock_Points::BeginPlay()
{
	Super::BeginPlay();
}


