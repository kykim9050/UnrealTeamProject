// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Net/UnrealNetwork.h"

AMainGameState::AMainGameState()
{

}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, CurStage);
	DOREPLIFETIME(AMainGameState, MeleeNum);
}

void AMainGameState::PushActor(uint8 _Index, AActor* _Actor)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	AllActor[_Index]->Actors.Add(_Actor);
}

UActorGroup* AMainGameState::GetActorGroup(uint8 _Index)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	return AllActor[_Index];
}

void AMainGameState::AddMeleeNum()
{
	AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();

	if (MaxMeleeNum <= MeleeNum)
	{
		return;
	}

	++MeleeNum;

	if (MaxMeleeNum == MeleeNum)
	{
		CurStage = EGameStage::VisitArmory;
		return;
	}
}

