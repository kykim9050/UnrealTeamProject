// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartProjectile.h"
#include "MainGameLevel/Object/ReportObject.h"

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

	FVector SpawnPos = GetActorLocation() + FTransform(GetControlRotation()).TransformVector(GunOffset);
	ABossHeartProjectile* Bullet = GetWorld()->SpawnActor<ABossHeartProjectile>(ProjectileUClass, SpawnPos, GetActorForwardVector().Rotation());
	if (nullptr != Bullet)
	{
		Bullet->SetDamage(SettingData->BaseData->RangedAttackDamage);
	}
}

void ABossHeart::DropItem()
{
	Super::DropItem();

	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z -= 130.0f;

	AReportObject* ReportObject = GetWorld()->SpawnActor<AReportObject>(SpawnLocation, FRotator::ZeroRotator);
}
