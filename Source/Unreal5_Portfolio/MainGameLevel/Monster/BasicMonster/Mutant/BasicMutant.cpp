// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"

void ABasicMutant::BeginPlay()
{
	SettingData = NewObject<UBasicMutantData>(this);
	SettingData->bScream = true;
	
	Super::BeginPlay();
}
