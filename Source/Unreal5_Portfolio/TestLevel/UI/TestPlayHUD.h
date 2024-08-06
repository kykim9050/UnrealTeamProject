// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/UI/MainParentHUD.h"
#include "Global/GlobalHUD.h"
#include "Global/ContentsEnum.h"
#include "TestPlayHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestPlayHUD : public AMainParentHUD
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	void AllUISetting() override;

	void AllUIOn() override;

	UPROPERTY(BlueprintReadOnly)
	TMap<EUserWidgetType, UUserWidget*> AllTestPlayWidgets;
};
