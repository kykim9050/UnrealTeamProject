// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/Notify/BossHeartSpawnProjectile.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"

void UBossHeartSpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ABossHeart* Heart = MeshComp->GetOwner<ABossHeart>();
	if (nullptr == Heart)
	{
		return;
	}

	Heart->Shooting();
}
