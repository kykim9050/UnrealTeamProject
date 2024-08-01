// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Zombie/BasicZombie.h"
#include "MainGameLevel/Monster/BasicMonster/Zombie/BasicZombieData.h"

void ABasicZombie::BeginPlay()
{
	SettingData = NewObject<UBasicZombieData>(this);
	SettingData->bScream = false;
	
	Super::BeginPlay();
}
