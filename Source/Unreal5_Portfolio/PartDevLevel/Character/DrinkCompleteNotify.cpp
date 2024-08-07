// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/DrinkCompleteNotify.h"
#include "ParentsCharacter.h"

void UDrinkCompleteNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AParentsCharacter* Actor = MeshComp->GetOwner<AParentsCharacter>();

	if (nullptr == Actor)
	{
		return;
	}

	Actor->AnimationEnd();
}
