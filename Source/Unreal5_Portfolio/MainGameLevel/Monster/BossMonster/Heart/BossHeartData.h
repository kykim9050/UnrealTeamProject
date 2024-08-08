// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BossMonsterData.h"
#include "BossHeartData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBossHeartData : public UBossMonsterData
{
	GENERATED_BODY()
	
public:
	FVector WalkDir = FVector::ZeroVector;

};
