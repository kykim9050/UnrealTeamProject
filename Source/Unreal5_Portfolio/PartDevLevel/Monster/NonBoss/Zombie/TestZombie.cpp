// Fill out your copyright notice in the Description page of Project Settings.


#include "TestZombie.h"
#include "Global/ContentsLog.h"

void ATestZombie::BeginPlay()
{
	Super::BeginPlay();

	ZombieSettingData = Cast<UTestZombieData>(SettingData);
	
	if (nullptr == ZombieSettingData)
	{
		LOG(MonsterLog, Fatal, TEXT("ZombieSettingData Is Nullptr"));
		return;
	}
}
