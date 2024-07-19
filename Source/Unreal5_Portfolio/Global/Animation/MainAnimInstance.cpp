// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"

void UMainAnimInstance::ChangeAnimation(uint8 Key)
{
	if (false == AnimMontages.Contains(Key))
	{
		LOG(GlobalLog, Fatal, "AnimMontages is Empty");
		return;
	}

	UAnimMontage* NextMontage = AnimMontages[Key];

	if (nullptr == NextMontage)
	{
		LOG(GlobalLog, Fatal, "Montage is nullptr");
		return;
	}

	UAnimMontage* CurMontage = GetCurrentActiveMontage();

	if (CurMontage != NextMontage)
	{
		Montage_Play(NextMontage);
	}
}

void UMainAnimInstance::PushAnimation(uint8 Key, UAnimMontage* Montage)
{
	if (true == AnimMontages.Contains(Key))
	{
		return;
	}

	AnimMontages.Add(Key, Montage);
}

