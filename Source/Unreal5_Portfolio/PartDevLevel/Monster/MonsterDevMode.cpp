// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/MonsterDevMode.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"

void AMonsterDevMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 1; i++)
	{
		FString MonsterType = "MonsterType_1";
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		const FMonsterDataRow* MonsterData = MainGameInst->GetMonsterData(FName(MonsterType));

		FTransform Transform;
		Transform.SetLocation(FVector(-270.0f + i * 100.0f, -40.0f, 298.0f));
		GetWorld()->SpawnActor<AActor>(MonsterData->GetMonsterUClass(), Transform);
	}
}
