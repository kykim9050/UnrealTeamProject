// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Animation/BasicMonsterAttackNotify.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"

void UBasicMonsterAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->SetAttackCollision(true);
	}
}

void UBasicMonsterAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABasicMonsterBase* Monster = Cast<ABasicMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->SetAttackCollision(false);
	}
}
