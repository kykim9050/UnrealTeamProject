// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Character/TestPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"

ATestPlayerState::ATestPlayerState()
{
}

void ATestPlayerState::InitPlayerData()
{
	if (-1.0f == PlayerHp)
	{
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
	}
	int a = 0;
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATestPlayerState, PlayerHp);
}

void ATestPlayerState::HealHp_Implementation()
{
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
}

void ATestPlayerState::AddDamage_Implementation(float _Damage)
{
	PlayerHp -= _Damage;
}