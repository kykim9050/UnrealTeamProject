// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HeadNameWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UHeadNameWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	//void InitWidget() override;

	UHeadNameWidgetComponent();

	UFUNCTION()
	void BilboardRotate(FVector _WorldLocation);

	UFUNCTION()
	void SetHeadNameRelativeLocation(FVector _Loc);

	UFUNCTION()
	void SetHeadNameRelativeRotation(FVector _Rot);

	UFUNCTION()
	void SetHeadNameWidgetText(FText _Name);
};
