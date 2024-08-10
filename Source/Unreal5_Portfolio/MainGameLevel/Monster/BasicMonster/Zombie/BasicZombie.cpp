// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Zombie/BasicZombie.h"
#include "MainGameLevel/Monster/BasicMonster/Zombie/BasicZombieData.h"


void ABasicZombie::InitData(const FMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	ZombieSettingData = NewObject<UBasicZombieData>(this);
	ZombieSettingData->bScream = false;

	SettingData = ZombieSettingData;
}
