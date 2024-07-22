// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/MonsterDevMode.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"

void AMonsterDevMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterDevMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// 새로 로그인한 플레이어 처리
	ATestPlayerState* NewPlayerState = NewPlayer->GetPlayerState<ATestPlayerState>();
	NewPlayerState->InitPlayerData();
}
