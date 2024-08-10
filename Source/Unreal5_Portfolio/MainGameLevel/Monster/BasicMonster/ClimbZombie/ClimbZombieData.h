// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
#include "ClimbZombieData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UClimbZombieData : public UBasicMonsterData
{
	GENERATED_BODY()

public:
	float ClimbSpeed = 150.0f;
	
};
