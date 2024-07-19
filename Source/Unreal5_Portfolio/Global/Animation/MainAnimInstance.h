// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

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
	void PushAnimation(EnumType Key, UAnimMontage* Montage)
	{
		PushAnimation(static_cast<uint8>(Key), Montage);
	}

	void PushAnimation(uint8 Key, UAnimMontage* Montage);

	TMap<uint8, UAnimMontage*> GetAnimMontages()
	{
		return AnimMontages;
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key)
	{
		return AnimMontages[Key];
	}

private:
	UPROPERTY()
	TMap<uint8, UAnimMontage*> AnimMontages;
};
