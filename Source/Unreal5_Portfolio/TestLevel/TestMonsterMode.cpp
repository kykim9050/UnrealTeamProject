// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestMonsterMode.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/MonsterDataRow.h"

void ATestMonsterMode::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FMonsterDataRow* MonsterData = MainGameInst->GetMonsterData(TEXT("MonsterType_1"));

	FTransform Transform;
	Transform.SetLocation({ 0.0f, 0.0f, 500.0f });
	GetWorld()->SpawnActor<AActor>(MonsterData->GetMonsterUClass(), Transform);
}
