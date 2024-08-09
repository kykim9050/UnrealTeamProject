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
public:
	UFUNCTION(BlueprintCallable)
	void SetTimerCurStage(EGameStage _SetStage);
	UFUNCTION(BlueprintCallable)
	void SetTimer(int _Min, int _Second);
	void SetTimer(int _Hour,int _Min,int _Second);


	FText T_Time;
	FTimespan NowTimeSpan;
};
