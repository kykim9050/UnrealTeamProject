// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"
#include <Net/UnrealNetwork.h>

AMainPlayerState::AMainPlayerState()
{

}

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerState, PlayerHp);
}

void AMainPlayerState::InitPlayerData()
{
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
}

void AMainPlayerState::AddDamage(float _Damage)
{
	PlayerHp -= _Damage;
}
