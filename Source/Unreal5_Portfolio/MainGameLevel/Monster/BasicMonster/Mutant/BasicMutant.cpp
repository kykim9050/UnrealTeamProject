// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"
#include "MotionWarpingComponent.h"

ABasicMutant::ABasicMutant()
{
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void ABasicMutant::InitData(const FMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	MutantSettingData = NewObject<UBasicMutantData>(this);
	MutantSettingData->OriginPos = GetActorLocation();
	MutantSettingData->BaseData = BaseData;
	MutantSettingData->bScream = true;

	SettingData = MutantSettingData;
}
