// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"

ABossHeart::ABossHeart()
{
	BossHeartSettingData = CreateDefaultSubobject<UBossHeartData>(TEXT("DataComponent"));
	BossHeartSettingData->SetIsReplicated(true);
}

void ABossHeart::InitData(const FBossMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	BossHeartSettingData->BaseData = BaseData;
	BossHeartSettingData->Hp = BaseData->MaxHp;

	SettingData = BossHeartSettingData;
}
