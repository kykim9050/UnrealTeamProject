// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TestTitleMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestTitleMode : public AGameMode
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ListenServerOn();
};
