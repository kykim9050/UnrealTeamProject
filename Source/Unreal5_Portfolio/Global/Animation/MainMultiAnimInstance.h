// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainMultiAnimInstance.generated.h"


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
class UNREAL5_PORTFOLIO_API UMainMultiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void ChangeAnimation(EnumType Key, int GroupIndex)
	{
		ChangeAnimation(static_cast<uint8>(Key), GroupIndex);
	}

	void ChangeAnimation(uint8 Key, int GroupIndex);

	template<typename EnumType>
	void PushAnimation(EnumType Key, const FAnimMontageGroup& AnimMontageGroup)
	{
		PushAnimation(static_cast<uint8>(Key), AnimMontageGroup);
	}

	void PushAnimation(uint8 Key, const FAnimMontageGroup& AnimMontageGroup);

	template<typename EnumType>
	UAnimMontage* GetKeyAnimMontage(EnumType Key, int GroupIndex)
	{
		return GetKeyAnimMontage(static_cast<uint8>(Key), GroupIndex);
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key, int GroupIndex)
	{
		return AllAnimMontages[Key].AnimMontages[GroupIndex];
	}

protected:
	UPROPERTY()
	TMap<uint8, FAnimMontageGroup> AllAnimMontages;
	
};
