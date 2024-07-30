// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/TestMonsterSpawner.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "TestLevel/Character/TestCharacter.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"

#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATestMonsterSpawner::ATestMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default Root
	UBillboardComponent* Root = CreateDefaultSubobject<UBillboardComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	// Create TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnTriggerBox"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATestMonsterSpawner::TriggerBoxBeginOverlap);
	TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	TriggerBox->SetCanEverAffectNavigation(false);
	TriggerBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	TimeCount = SpawnDelayTime;
	TriggerBox->SetActive(TriggerIsActive);
}

// Called every frame
void ATestMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 트리거 박스 활성화 또는 클라이언트 일시 return
	if (true == TriggerIsActive || false == HasAuthority())
	{
		return;
	}

	if (0.0f < TimeCount)
	{
		TimeCount -= DeltaTime;
		return;
	}

	if (0 >= TotalSpawnCount)
	{
		Destroy();
		return;
	}

	SpawnTestMonster();
	TimeCount = SpawnDelayTime;
}

void ATestMonsterSpawner::SpawnTestMonster()
{
	UMainGameInstance* MainInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	int Size = MonsterUClass.Num() - 1;
	FVector CurPos = GetActorLocation();

	for (int32 i = 0; i < SpawnMonsterCount; i++)
	{
		int TypeIndex = MainInst->Random.RandRange(0, Size);
		float SpawnRadius = MainInst->Random.FRandRange(0, MaxSpawnRadius);
		FVector SpawnLocation = CurPos + MainInst->Random.GetUnitVector().GetSafeNormal2D() * SpawnRadius;
		ATestMonsterBase* NewMonster = GetWorld()->SpawnActor<ATestMonsterBase>(MonsterUClass[TypeIndex], SpawnLocation, FRotator::ZeroRotator);

		if (nullptr != NewMonster && true == IsChasePlayer)
		{
			NewMonster->SetChasePlayer();
		}
	}

	--TotalSpawnCount;
}

void ATestMonsterSpawner::TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATestCharacter* Player = Cast<ATestCharacter>(OtherActor);
	if (nullptr == Player)
	{
		return;
	}

	TriggerIsActive = false;
	TriggerBox->SetActive(TriggerIsActive);
}

