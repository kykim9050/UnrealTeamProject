// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterGameState.h"

void ATestMonsterGameState::PushActor(uint8 _Index, AActor* _Actor)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}
	
	AllActor[_Index]->Actors.Add(_Actor);
}
