// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainPlayerState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "MainGameLevel/Player/MainPlayerController.h"
#include "MainGameLevel/Player/MainCharacter.h"
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
	if (nullptr != MainGameInst)
	{
		PlayerHp = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetHp();
	}
}

float AMainPlayerState::GetPlayerHp() const
{
	return PlayerHp;
}

void AMainPlayerState::AddDamage_Implementation(float _Damage)
{
	PlayerHp -= _Damage;

	if (0 >= PlayerHp)
	{
		AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwner());
		if (nullptr == MainPlayerController)
		{
			MainPlayerController = Cast<AMainPlayerController>(GetPawn());

			if (nullptr == MainPlayerController)
			{
				return;
			}
		}

		AMainCharacter* MyMainCharacter = Cast<AMainCharacter>(MainPlayerController->GetCharacter());
		if (nullptr != MyMainCharacter)
		{
			MyMainCharacter->ChangeIsFaint();
		}
	}
}
