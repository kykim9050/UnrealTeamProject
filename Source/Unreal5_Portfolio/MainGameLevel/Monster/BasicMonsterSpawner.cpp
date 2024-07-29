// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonsterSpawner.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"

#include "Components/BoxComponent.h"

// Sets default values
ABasicMonsterSpawner::ABasicMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	//TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AYourCustomActor::OnTriggerBox1Overlap);

}

// Called when the game starts or when spawned
void ABasicMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TimeCount = SpawnDelayTime;
}

// Called every frame
void ABasicMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (false == HasAuthority())
	{
		return;
	}

	if (0.0f >= TimeCount)
	{
		if (0 >= TotalSpawnCount)
		{
			Destroy();
		}

		SpawnBasicMonster();

		TimeCount = SpawnDelayTime;
		return;
	}

	TimeCount -= DeltaTime;
}

void ABasicMonsterSpawner::SpawnBasicMonster()
{
	UMainGameInstance* MainInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	int Size = MonsterUClass.Num() - 1;
	FVector CurPos = GetActorLocation();

	for (int32 i = 0; i < SpawnMonsterCount; i++)
	{
		int TypeIndex = MainInst->Random.RandRange(0, Size);
		float SpawnRadius = MainInst->Random.FRandRange(0, MaxSpawnRadius);
		FVector SpawnLocation = CurPos + MainInst->Random.GetUnitVector().GetSafeNormal2D() * SpawnRadius;
		GetWorld()->SpawnActor<AActor>(MonsterUClass[TypeIndex], SpawnLocation, FRotator::ZeroRotator);
	}

	--TotalSpawnCount;
}

