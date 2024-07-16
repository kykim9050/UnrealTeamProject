// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Character/TestPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"

ATestPlayerState::ATestPlayerState()
{

}

void ATestPlayerState::InitPlayerData(int _PlayerNumber)
{
	//UMainGameInstance* MainGameInst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
	
	SetPlayerNumber(_PlayerNumber);
}

void ATestPlayerState::SetPlayerHp(float _Hp)
{
	PlayerHp = _Hp;
}

void ATestPlayerState::SetPlayerNumber(int _Num)
{
	PlayerNumber = _Num;
}

void ATestPlayerState::SetAllPlayerStates(TArray<ATestPlayerState*> _Arr)
{
	AllPlayerStates = _Arr;	// µ¤¾î¾º¿ò
}

void ATestPlayerState::AddDamage(float _Damage)
{
	PlayerHp -= _Damage;
}