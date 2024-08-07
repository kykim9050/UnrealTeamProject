// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/Notify/BossKrakenSpawnProjectile.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"

void UBossKrakenSpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ABossKraken* Kraken = MeshComp->GetOwner<ABossKraken>();
	if (nullptr == Kraken)
	{
		return;
	}

	Kraken->SpawnRock();
}