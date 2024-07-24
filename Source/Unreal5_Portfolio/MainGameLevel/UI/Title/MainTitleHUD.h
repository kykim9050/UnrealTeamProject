// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/UI/MainParentHUD.h"
#include "MainTitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainTitleHUD : public AMainParentHUD
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
	void AllUISetting() override;
};
