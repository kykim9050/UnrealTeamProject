// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"

void ABossKraken::InitData(const FBossMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	BossKrakenSettingData = NewObject<UBossKrakenData>(this);
	BossKrakenSettingData->Hp = 100.0f;

	SettingData = BossKrakenSettingData;
}
