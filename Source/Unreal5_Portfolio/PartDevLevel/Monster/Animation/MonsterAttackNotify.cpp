// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/MonsterAttackNotify.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

void UMonsterAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->SetAttackCollision(true);
	}

	ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(MeshComp->GetOwner());
	if (nullptr != BossMonster)
	{
		BossMonster->SetAttackCollision(true);
	}
}

void UMonsterAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->SetAttackCollision(false);
	}

	ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(MeshComp->GetOwner());
	if (nullptr != BossMonster)
	{
		BossMonster->SetAttackCollision(false);
	}
}
