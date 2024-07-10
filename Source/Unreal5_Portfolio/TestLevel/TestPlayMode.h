// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "TestPlayMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestPlayMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlayerToDropItem(FName _ItemName, FTransform _Transform);
};
