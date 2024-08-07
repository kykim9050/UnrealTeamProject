// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GetCurStage_UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Timer_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTimer_UserWidget : public UGetCurStage_UserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SetTimerCurStage(EGameStage _SetStage);
};
