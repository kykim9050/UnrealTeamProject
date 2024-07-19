// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainAnimInstance.h"
#include "BossMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBossMonsterAnimInstance : public UMainAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AnimNotify_RAttackEnd();
	
};
