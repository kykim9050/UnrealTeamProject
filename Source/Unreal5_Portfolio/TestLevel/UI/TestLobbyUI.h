// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestLobbyUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTestLobbyUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void TravelToNext();

	UFUNCTION(BlueprintCallable)
	bool IsServer();
};
