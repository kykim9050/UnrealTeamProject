// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainMultiAnimInstance.h"
#include "MonsterRandomAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMonsterRandomAnimInstance : public UMainMultiAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void SetRandomAnimIndex(EnumType Key, int& Index)
	{
		SetRandomAnimIndex(static_cast<uint8>(Key), Index);
	}

	void SetRandomAnimIndex(uint8 Key, int& Index);
	
};
