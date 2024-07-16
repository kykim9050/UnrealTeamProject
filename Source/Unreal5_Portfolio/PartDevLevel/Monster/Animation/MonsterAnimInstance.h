// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMonsterAnimInstance : public UMainAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void PushRandomAnimation(EnumType _Key, struct FAnimMontageGroup _MontageGroup)
	{
		PushRandomAnimation(static_cast<uint8>(_Key), _MontageGroup);
	}

	UFUNCTION(Reliable, Server)
	void PushRandomAnimation(uint8 _Key, struct FAnimMontageGroup _MontageGroup);
	void PushRandomAnimation_Implementation(uint8 _Key, struct FAnimMontageGroup _MontageGroup);

private:
	UFUNCTION(Reliable, NetMulticast)
	void PushMontage(uint8 _Key, UAnimMontage* _Montage);
	void PushMontage_Implementation(uint8 _Key, UAnimMontage* _Montage);

};
