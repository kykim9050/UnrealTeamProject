// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "TestLevel/Character/TestCharacter.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerPlayer = Cast<ATestCharacter>(GetOwningActor());
	PlayerMesh = OwnerPlayer->GetMesh();

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (nullptr == OwnerPlayer)
	{
		return;
	}

	PlayerState = OwnerPlayer->StateValue;
}