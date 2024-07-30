// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Data/BasicMonsterData.h"
#include "Net/UnrealNetwork.h"

void UBasicMonsterData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBasicMonsterData, Hp);
}
