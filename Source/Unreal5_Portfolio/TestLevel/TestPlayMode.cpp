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

	UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	const FMonsterDataRow* MonsterData = MainGameInst->GetMonsterData(TEXT("MonsterType_1"));

	for (int i = 0; i < 5; i++)
	{
		FTransform Transform;
		Transform.SetLocation({ 500.0f, -200.0f + (100.0f * i), 500.0f});
		GetWorld()->SpawnActor<AActor>(MonsterData->GetMonsterUClass(), Transform);
	}
}

void ATestPlayMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

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
