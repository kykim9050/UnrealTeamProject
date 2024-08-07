// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenProjectileSpawnPoint.h"

#include "Components/BoxComponent.h"

ABossKraken::ABossKraken()
{
	BodyComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollision"));
	BodyComponent->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UBossKrakenProjectileSpawnPoint>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ABossKraken::InitData(const FBossMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	BossKrakenSettingData = NewObject<UBossKrakenData>(this);
	BossKrakenSettingData->BaseData = BaseData;
	BossKrakenSettingData->Hp = 100.0f;

	SettingData = BossKrakenSettingData;
}
