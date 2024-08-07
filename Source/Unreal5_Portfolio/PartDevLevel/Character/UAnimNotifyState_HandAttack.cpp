// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/UAnimNotifyState_HandAttack.h"
#include "TestLevel/Character/TestCharacter.h"
#include "ParentsCharacter.h"
#include "TestFPVCharacter.h"

void UUAnimNotifyState_HandAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AParentsCharacter* ParentsPlayer = MeshComp->GetOwner<AParentsCharacter>();
	if (nullptr == ParentsPlayer)
	{
		return;
	}
	ParentsPlayer->ChangeHandAttackCollisionProfile(TEXT("PlayerHandAttack"));
}

void UUAnimNotifyState_HandAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UUAnimNotifyState_HandAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AParentsCharacter* ParentsPlayer = MeshComp->GetOwner<AParentsCharacter>();
	if (nullptr == ParentsPlayer)
	{
		return;
	}
	ParentsPlayer->ChangeHandAttackCollisionProfile(TEXT("NoCollision"));
}
