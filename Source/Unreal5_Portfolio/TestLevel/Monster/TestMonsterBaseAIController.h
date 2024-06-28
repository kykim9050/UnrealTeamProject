// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestMonsterBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestMonsterBaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

};
