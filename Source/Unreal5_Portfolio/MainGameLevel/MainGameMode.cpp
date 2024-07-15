// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/MainGameMode.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/MonsterSpawnerDataRow.h"
#include "Player/MainPlayerState.h"
#include "Monster/MonsterSpawner.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateMonsterSpawner(TEXT("TypeOnce_0"));
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

void AMainGameMode::CreateMonsterSpawner(FName _DataTableRowName)
{
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	const FMonsterSpawnerDataRow* MonsterSpawnerData = MainGameInst->GetMonsterSpawnerData(_DataTableRowName);

	TArray<FMonsterSpawnerInfo> SpawnerInfo = MonsterSpawnerData->GetSpawnerInfo();
	for (int i = 0; i < SpawnerInfo.Num(); i++)
	{
		AMonsterSpawner* NewMonsterSpawner = GetWorld()->SpawnActor<AMonsterSpawner>();
		NewMonsterSpawner->InitSpawner(SpawnerInfo[i].Type, SpawnerInfo[i].Location, SpawnerInfo[i].Ridus, SpawnerInfo[i].MinSpawnNum, SpawnerInfo[i].MaxSpawnNum);
	}
}

