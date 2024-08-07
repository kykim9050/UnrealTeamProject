// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/AnimNotifyState_Muzzle_Particle.h"
#include "TestLevel/Character/TestCharacter.h"
#include "MainGameLevel/Player/MainCharacter.h"

void UAnimNotifyState_Muzzle_Particle::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ATestCharacter* PlayCharacter = MeshComp->GetOwner<ATestCharacter>();
	if (nullptr != PlayCharacter)
	{
		if (true == MeshComp->bOwnerNoSee)
		{
			//PlayCharacter->ShowMuzzle();
		}
	}
}

void UAnimNotifyState_Muzzle_Particle::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_Muzzle_Particle::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
