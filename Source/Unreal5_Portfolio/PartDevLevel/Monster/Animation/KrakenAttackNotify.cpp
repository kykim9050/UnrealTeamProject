// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/KrakenAttackNotify.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

void UKrakenAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr == Monster)
	{
		return;
	}

	//if (false == Monster->HasAuthority())
	//{
	//	return;
	//}

	Monster->SpawnParticle();
}
