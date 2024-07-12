// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestCrosshairUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTestCrosshairUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime) override;


	bool ClickedCrosshair(float _Size);
	bool DefaultCrosshair(float _Size);

	bool ClickedCrosshair_scale(float _Size);
	bool DefaultCrosshair_scale(float _Size);

	UPanelWidget* PanelWidget = nullptr;
	TArray<UWidget*> AllChildren;
	TArray<UWidget*> VerticalCrosshair;
	TArray<UWidget*> HorizontalCrosshair;

	bool DefaultFlag = false;

private:
	float dx[4] = { 0.f, 0.f, -1.f, 1.f }; // 위, 아래, 왼, 오른
	float dy[4] = { -1.f, 1.f, 0.f, 0.f };
};
