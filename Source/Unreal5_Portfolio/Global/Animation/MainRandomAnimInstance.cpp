// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Animation/MainRandomAnimInstance.h"
#include "Global/ContentsLog.h"

void UMainRandomAnimInstance::ChangeAnimation(uint8 _Key)
{
	if (false == AnimMontages.Contains(_Key))
	{
		LOG(GlobalLog, Fatal, TEXT("AnimMontages false"));
		return;
	}

	UAnimMontage* Montage = AnimMontages[_Key];

	if (nullptr == Montage)
	{
		LOG(GlobalLog, Fatal, TEXT("Montage is nullptr"));
		return;
	}

	UAnimMontage* PrevMontage = GetCurrentActiveMontage();

	if (PrevMontage != Montage)
	{
		Montage_Play(Montage);
	}
}

void UMainRandomAnimInstance::PushAnimation(uint8 _Key, UAnimMontage* _Montage)
{
	if (true == AnimMontages.Contains(_Key))
	{
		return;
	}

	AnimMontages.Add(_Key, _Montage);
}