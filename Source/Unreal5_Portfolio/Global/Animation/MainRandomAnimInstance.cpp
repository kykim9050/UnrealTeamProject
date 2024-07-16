// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Animation/MainRandomAnimInstance.h"
#include "Global/ContentsLog.h"

void UMainRandomAnimInstance::ChangeAnimation(uint8 _Key)
{
	if (false == AllAnimMontages.Contains(_Key))
	{
		LOG(GlobalLog, Fatal, TEXT("AnimMontages false"));
		return;
	}

	FAnimMontageGroup Montage = AllAnimMontages[_Key];

	if (0 == Montage.AnimMontages.Num())
	{
		LOG(GlobalLog, Fatal, TEXT("Montage is nullptr"));
		return;
	}

	//UAnimMontage* PrevMontage = GetCurrentActiveMontage();

	//if (PrevMontage != Montage)
	//{
	//	Montage_Play(Montage);
	//}
}

void UMainRandomAnimInstance::PushAnimation(uint8 _Key, UAnimMontage* _Montage)
{
	if (true == AllAnimMontages.Contains(_Key))
	{
		return;
	}

	AllAnimMontages[_Key].AnimMontages.Add(_Montage);
}