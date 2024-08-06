// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/AnimNotify_EndMontage.h"
#include "ParentsCharacter.h"

UAnimNotify_EndMontage::UAnimNotify_EndMontage()
{
	bShouldFireInEditor = false;
}

void UAnimNotify_EndMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AParentsCharacter* Actor = MeshComp->GetOwner<AParentsCharacter>();

	if (nullptr == Actor)
	{
		return;
	}
	
	Actor->AnimationEnd();


}
