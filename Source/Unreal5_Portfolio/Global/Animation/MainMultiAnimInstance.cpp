// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Animation/MainMultiAnimInstance.h"
#include "Global/ContentsLog.h"

void UMainMultiAnimInstance::ChangeAnimation(uint8 Key, int GroupIndex)
{
	if (false == AllAnimMontages.Contains(Key))
	{
		LOG(GlobalLog, Fatal, "AnimMontages is Empty");
		return;
	}

	UAnimMontage* NextMontage = AllAnimMontages[Key].AnimMontages[GroupIndex];

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

void UMainMultiAnimInstance::PushAnimation(uint8 Key, const FAnimMontageGroup& AnimMontageGroup)
{
	if (true == AllAnimMontages.Contains(Key))
	{
		return;
	}

	AllAnimMontages.Add(Key, FAnimMontageGroup());
	for (int32 i = 0; i < AnimMontageGroup.AnimMontages.Num(); i++)
	{
		AllAnimMontages[Key].AnimMontages.Add(AnimMontageGroup.AnimMontages[i]);
	}
}
