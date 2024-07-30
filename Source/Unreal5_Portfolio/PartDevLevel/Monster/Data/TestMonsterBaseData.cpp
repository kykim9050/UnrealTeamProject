// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Data/TestMonsterBaseData.h"
#include "Net/UnrealNetwork.h"

void UTestMonsterBaseData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTestMonsterBaseData, Hp);
}