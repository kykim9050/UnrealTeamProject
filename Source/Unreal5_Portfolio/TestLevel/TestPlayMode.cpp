// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestPlayMode.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Item/RangedWP.h"
#include "Global/MainGameInstance.h"
#include "Character/TestPlayerState.h"

void ATestPlayMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPlayMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// 새로 로그인한 플레이어 처리
	//ATestPlayerState* NewPlayerState = NewPlayer->GetPlayerState<ATestPlayerState>();
	//NewPlayerState->InitPlayerData();
}

void ATestPlayMode::GPlayerToDropItem_Implementation(FName _ItemName, FTransform _Transform)
{
	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	//const FItemDataRow* ItemBase = MainGameInst->GetItemData(_ItemName);


	const FItemDataRow* ItemBase = MainGameInst->GetItemData(FName("TestRifle"));
	GetWorld()->SpawnActor<AActor>(ItemBase->GetItemUClass(), _Transform);
}

void ATestPlayMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ATestPlayMode, Value);
}
