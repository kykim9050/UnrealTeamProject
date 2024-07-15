// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainRandomAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMainRandomAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void ChangeAnimation(EnumType _Key)
	{
		ChangeAnimation(static_cast<uint8>(_Key));
	}

	virtual void ChangeAnimation(uint8 _Key);

	template<typename EnumType>
	void PushAnimation(EnumType _Key, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<uint8>(_Key), _Montage);
	}

	void PushAnimation(uint8 _Key, class UAnimMontage* _Montage);

	TMap<uint8, class UAnimMontage*> GetAnimMontages()
	{
		return AnimMontages;
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key)
	{
		return AnimMontages[Key];
	}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, class UAnimMontage*> AnimMontages;
};
