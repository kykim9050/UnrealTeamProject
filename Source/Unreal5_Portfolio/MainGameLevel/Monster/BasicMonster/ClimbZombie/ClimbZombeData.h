// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
#include "ClimbZombeData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UClimbZombeData : public UBasicMonsterData
{
	GENERATED_BODY()

public:
	float ClimbSpeed = 75.0f;
	
};
