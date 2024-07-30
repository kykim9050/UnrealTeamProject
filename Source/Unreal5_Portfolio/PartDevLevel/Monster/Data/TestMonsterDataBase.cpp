// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Data/TestMonsterDataBase.h"
#include "Net/UnrealNetwork.h"

void UTestMonsterDataBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTestMonsterDataBase, Hp);
}