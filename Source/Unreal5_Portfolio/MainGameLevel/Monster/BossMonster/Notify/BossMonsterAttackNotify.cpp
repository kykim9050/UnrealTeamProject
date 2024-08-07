// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Notify/BossMonsterAttackNotify.h"
#include "MainGameLevel/Monster/Base/BossMonsterBase.h"

#include "Components/SphereComponent.h"

void UBossMonsterAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ABossMonsterBase* Monster = Cast<ABossMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->GetAttackComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void UBossMonsterAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ABossMonsterBase* Monster = Cast<ABossMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->GetAttackComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
