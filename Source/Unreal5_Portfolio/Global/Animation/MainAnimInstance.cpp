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
		uint8 PrevKey = GetAnimationKey(CurMontage);

		if (true == AnimCallBack.Contains(PrevKey))
		{
			UAnimCallBack* CallBackObject = AnimCallBack[PrevKey];

			if (nullptr != CallBackObject)
			{
				CallBackObject->CallBack(PrevKey, CurMontage);
			}
		}

		Montage_Play(NextMontage);
	}
}

void UMainAnimInstance::PushAnimation(uint8 Key, UAnimMontage* Montage, TFunction<void(uint8, UAnimMontage*)> _CallBack)
{
	if (true == AnimMontages.Contains(Key))
	{
		return;
	}

	AnimMontages.Add(Key, Montage);

	if (_CallBack != nullptr)
	{
		UAnimCallBack* NewCallBack = NewObject<UAnimCallBack>(this);
		NewCallBack->CallBack = _CallBack;
		AnimCallBack.Add(Key, NewCallBack);
	}
}

void UMainAnimInstance::SetEndCallBackPush(uint8 Key, TFunction<void(uint8, UAnimMontage*)> _CallBack)
{
	if (_CallBack != nullptr)
	{
		UAnimCallBack* NewCallBack = NewObject<UAnimCallBack>(this);
		NewCallBack->CallBack = _CallBack;
		AnimCallBack.Add(Key, NewCallBack);
	}
}

uint8 UMainAnimInstance::GetAnimationKey(class UAnimMontage* _AnimMontage)
{
	for (TPair<uint8, class UAnimMontage*> Pair : AnimMontages)
	{
		if (Pair.Value == _AnimMontage)
		{
			return Pair.Key;
		}
	}

	return -1;
}

void UMainAnimInstance::ClearAnimMontages()
{
	AnimMontages.Empty();
}
