// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/MainGameMode.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Player/MainPlayerState.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

//void AMainGameMode::PostLogin(APlayerController* NewPlayer)
//{
//	Super::PostLogin(NewPlayer);
//
//	AMainPlayerState* MainPlayerController = Cast<AMainPlayerState>(NewPlayer->PlayerState);
//	MainPlayerController->InitPlayerData();
//}


