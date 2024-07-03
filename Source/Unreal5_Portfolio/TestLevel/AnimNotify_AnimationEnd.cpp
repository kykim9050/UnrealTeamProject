// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/AnimNotify_AnimationEnd.h"

#include "TestLevel/Monster/TestMonsterBase.h"

UAnimNotify_AnimationEnd::UAnimNotify_AnimationEnd()
{
}

void UAnimNotify_AnimationEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->SetAttackAnimationEnd(true);
	}
}