// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainRandomAnimInstance.generated.h"

USTRUCT()
struct UNREAL5_PORTFOLIO_API FAnimMontageGroup
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AnimMontages;

};

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

	TMap<uint8, FAnimMontageGroup> GetAnimMontages()
	{
		return AllAnimMontages;
	}

	FAnimMontageGroup GetKeyAnimMontage(uint8 Key)
	{
		return AllAnimMontages[Key];
	}

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, FAnimMontageGroup> AllAnimMontages;
};
