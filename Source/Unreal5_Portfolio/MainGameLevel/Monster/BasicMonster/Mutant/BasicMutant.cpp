// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"

void ABasicMutant::BeginPlay()
{
	MutantSettingData = NewObject<UBasicMutantData>(this);
	MutantSettingData->bScream = true;

	SettingData = MutantSettingData;
	Super::BeginPlay();
}
