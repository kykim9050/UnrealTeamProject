// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestPlayMode.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"

void ATestPlayMode::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FMonsterDataRow* MonsterData = MainGameInst->GetMonsterData(TEXT("MonsterType_1"));

	FTransform Transform;
	Transform.SetLocation({ 500.0f, 0.0f, 500.0f });
	GetWorld()->SpawnActor<AActor>(MonsterData->GetMonsterUClass(), Transform);
}
