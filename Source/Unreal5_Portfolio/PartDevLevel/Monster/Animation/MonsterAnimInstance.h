// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainMultiAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMonsterAnimInstance : public UMainMultiAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void SetRandomAniIndex(EnumType Key, int& Index)
	{
		SetRandomAniIndex(static_cast<uint8>(Key), Index);
	}

	void SetRandomAniIndex(uint8 Key, int& Index);

};