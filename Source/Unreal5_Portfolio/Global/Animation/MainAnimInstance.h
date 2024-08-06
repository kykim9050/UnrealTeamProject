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

	void SetEndCallBack(uint8 Key, TFunction<void(uint8, UAnimMontage*)> _CallBack = nullptr);

	TMap<uint8, UAnimMontage*> GetAnimMontages()
	{
		return AnimMontages;
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key)
	{
		return AnimMontages[Key];
	}

	uint8 GetAnimationKey(class UAnimMontage* _AnimMontage);

private:
	UPROPERTY()
	TMap<uint8, UAnimMontage*> AnimMontages;

	UPROPERTY()
	TMap<int32, UAnimCallBack*> AnimCallBack;
};
