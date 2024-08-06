// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/UI/MainParentHUD.h"
#include "MainGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainGameHUD : public AMainParentHUD
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
	void AllUISetting() override;

public:
	void AllUIOn() override;
};
