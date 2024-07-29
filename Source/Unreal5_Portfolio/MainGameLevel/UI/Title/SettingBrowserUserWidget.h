// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/UI/Common/DefaultButtonUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SettingBrowserUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API USettingBrowserUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* NameTextBox;

	UPROPERTY(meta = (BindWidget))
	class UDefaultButtonUserWidget* OkButton;

public:
	void NativeConstruct() override;

	UFUNCTION()
	void OnOkButtonClicked();
};
