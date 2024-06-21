// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TestLobbyMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestLobbyMode : public AGameMode
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	void ListenServerOn();
};
