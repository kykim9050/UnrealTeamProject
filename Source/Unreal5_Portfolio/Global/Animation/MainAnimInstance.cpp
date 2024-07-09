// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "TestLevel/Character/TestCharacter.h"

void UMainAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerPlayer = Cast<ATestCharacter>(TryGetPawnOwner());
}

void UMainAnimInstance::ChangeAnimation(uint8 _Key)
{
	if (false == AnimMontages.Contains(_Key))
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (false == AnimMontages.Contains(Key))"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* Montage = AnimMontages[_Key];

	if (nullptr == Montage)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == Montage)"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* PrevMontage = GetCurrentActiveMontage();

	if (PrevMontage != Montage)
	{
		Montage_Play(Montage);
	}
}

void UMainAnimInstance::PushAnimation(uint8 _Key, UAnimMontage* _Montage)
{
	if (true == AnimMontages.Contains(_Key))
	{
		return;
	}

	AnimMontages.Add(_Key, _Montage);
}

