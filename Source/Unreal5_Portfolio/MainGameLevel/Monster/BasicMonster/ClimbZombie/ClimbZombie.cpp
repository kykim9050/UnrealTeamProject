// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombie.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombeData.h"
#include "MotionWarpingComponent.h"

AClimbZombie::AClimbZombie()
{
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void AClimbZombie::InitData(const FMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	ClimbZombieSettingData = NewObject<UClimbZombeData>(this);
	ClimbZombieSettingData->OriginPos = GetActorLocation();
	ClimbZombieSettingData->BaseData = BaseData;
	ClimbZombieSettingData->bScream = false;

	SettingData = ClimbZombieSettingData;
}
