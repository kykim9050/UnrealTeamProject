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

void ABossHeart::Shooting()
{
	if (false == HasAuthority())
	{
		return;
	}

	//FVector InitPos = ProjectileSpawnPoint->GetComponentLocation();
	//for (int32 i = 0; i < ProjectileSpawnPoint->SpawnLocation.Num(); i++)
	//{
	//	FVector SpawnPos = InitPos + ProjectileSpawnPoint->SpawnLocation[i];
	//	FVector Direction = SpawnPos - GetActorLocation();
	//	Direction.Normalize();
	//
	//	ABossKrakenProjectile* Rock = GetWorld()->SpawnActor<ABossKrakenProjectile>(ProjectileUClass, SpawnPos, Direction.Rotation());
	//}
}
