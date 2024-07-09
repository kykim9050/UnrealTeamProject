// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "TestMinimapIconComponent.generated.h"

/**
 * 
 */
UCLASS(ShowCategories = (Mobility), ClassGroup = Paper2D, meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API UTestMinimapIconComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()

public:
	UTestMinimapIconComponent();
	void BeginPlay() override;
};
