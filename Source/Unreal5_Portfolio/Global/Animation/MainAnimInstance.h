// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

UCLASS(BlueprintType)
class UNREAL5_PORTFOLIO_API UAnimCallBack : public UObject
{
	GENERATED_BODY()

public :
	UAnimCallBack() {}
	~UAnimCallBack() {}

	TFunction<void(uint8, UAnimMontage*)> CallBack;
};

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void ChangeAnimation(EnumType Key)
	{
		ChangeAnimation(static_cast<uint8>(Key));
	}

	void ChangeAnimation(uint8 Key);

	template<typename EnumType>
	void PushAnimation(EnumType Key, UAnimMontage* Montage, TFunction<void(uint8, UAnimMontage*)> _CallBack = nullptr)
	{
		PushAnimation(static_cast<uint8>(Key), Montage, _CallBack);
	}

	void PushAnimation(uint8 Key, UAnimMontage* Montage, TFunction<void(uint8, UAnimMontage*)> _CallBack = nullptr);

	template<typename EnumType>
	void SetEndCallBack(EnumType Key, TFunction<void(uint8, UAnimMontage*)> _CallBack)
	{
		SetEndCallBackPush(static_cast<uint8>(Key), _CallBack);
	}

	void SetEndCallBackPush(uint8 Key, TFunction<void(uint8, UAnimMontage*)> _CallBack);

	TMap<uint8, UAnimMontage*> GetAnimMontages()
	{
		return AnimMontages;
	}

	template<typename EnumType>
	UAnimMontage* GetKeyAnimMontage(EnumType Key)
	{
		return GetKeyAnimMontage(static_cast<uint8>(Key));
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key)
	{
		return AnimMontages[Key];
	}

	void SetKeyAnimMontage(uint8 Key, class UAnimMontage* _AnimMontage)
	{
		AnimMontages[Key] = _AnimMontage;
	}

	uint8 GetAnimationKey(class UAnimMontage* _AnimMontage);

	void ClearAnimMontages();

private:
	UPROPERTY()
	TMap<uint8, UAnimMontage*> AnimMontages;

	UPROPERTY()
	TMap<int32, UAnimCallBack*> AnimCallBack;
};
