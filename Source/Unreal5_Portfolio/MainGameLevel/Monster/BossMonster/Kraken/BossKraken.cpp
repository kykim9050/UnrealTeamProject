// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenProjectileSpawnPoint.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenProjectile.h"

#include "Components/BoxComponent.h"

ABossKraken::ABossKraken()
{
	BossKrakenSettingData = CreateDefaultSubobject<UBossKrakenData>(TEXT("DataComponent"));
	BossKrakenSettingData->SetIsReplicated(true);
	
	BodyComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollision"));
	BodyComponent->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UBossKrakenProjectileSpawnPoint>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ABossKraken::InitData(const FBossMonsterDataRow* BaseData)
{
	Super::InitData(BaseData);

	SettingData = BossKrakenSettingData;
}

void ABossKraken::SpawnRock()
{
	if (false == HasAuthority())
	{
		return;
	}

	FVector InitPos = ProjectileSpawnPoint->GetComponentLocation();
	for (int32 i = 0; i < ProjectileSpawnPoint->SpawnLocation.Num(); i++)
	{
		FVector SpawnPos = InitPos + ProjectileSpawnPoint->SpawnLocation[i];
		FVector Direction = SpawnPos - GetActorLocation();
		Direction.Normalize();
	
		ABossKrakenProjectile* Rock = GetWorld()->SpawnActor<ABossKrakenProjectile>(ProjectileUClass, SpawnPos, Direction.Rotation());
		if (nullptr != Rock)
		{
			Rock->SetDamage(SettingData->BaseData->RangedAttackDamage);
		}
	}
}