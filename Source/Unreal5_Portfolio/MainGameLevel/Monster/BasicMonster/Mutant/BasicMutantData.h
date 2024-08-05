// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
#include "BasicMutantData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBasicMutantData : public UBasicMonsterData
{
	GENERATED_BODY()
	
public:
	float JumpAttackMinRange = 800.0f;
	float JumpAttackMaxRange = 1000.0f;

};
