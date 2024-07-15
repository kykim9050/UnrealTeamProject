// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Character/TestPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"

ATestPlayerState::ATestPlayerState()
{

}

void ATestPlayerState::InitPlayerData()
{
	//UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
}

void ATestPlayerState::SetPlayerHp(float _Hp)
{
	PlayerHp = _Hp;
}

void ATestPlayerState::AddDamage(float _Damage)
{
	PlayerHp -= _Damage;
}