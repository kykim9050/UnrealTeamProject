// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DataTable/MonsterDataRow.h"
#include "Net/UnrealNetwork.h"

void UTestMonsterData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTestMonsterData, Hp);
}