// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TestMonsterMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestMonsterMode : public AGameMode
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	
};
