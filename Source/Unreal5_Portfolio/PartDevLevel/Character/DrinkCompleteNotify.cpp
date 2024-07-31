// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/DrinkCompleteNotify.h"
#include "TestLevel/Character/TestCharacter.h"

void UDrinkCompleteNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ATestCharacter* PlayCharacter = MeshComp->GetOwner<ATestCharacter>();
	if (nullptr == PlayCharacter)
	{
		return;
	}

	PlayCharacter->DrinkComplete();
}
