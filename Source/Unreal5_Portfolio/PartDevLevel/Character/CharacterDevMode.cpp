// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/CharacterDevMode.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"

void ACharacterDevMode::BeginPlay()
{
	Super::BeginPlay();

	/*UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FMonsterDataRow* MonsterData = MainGameInst->GetMonsterData(TEXT("MonsterType_1"));

	for (int i = 0; i < 5; i++)
	{
		FTransform Transform;
		Transform.SetLocation({ 500.0f, -200.0f + (100.0f * i), 500.0f });
		GetWorld()->SpawnActor<AActor>(MonsterData->GetMonsterUClass(), Transform);
	}*/
}
