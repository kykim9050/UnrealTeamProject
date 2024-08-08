// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};
