// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombie.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombieData.h"
#include "MotionWarpingComponent.h"

AClimbZombie::AClimbZombie()
{
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void AClimbZombie::InitData(const FMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	ClimbZombieSettingData = NewObject<UClimbZombieData>(this);
	ClimbZombieSettingData->bScream = false;

	SettingData = ClimbZombieSettingData;
}
