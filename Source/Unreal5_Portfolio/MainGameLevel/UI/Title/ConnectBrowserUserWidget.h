// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ComboBoxString.h"
#include "Components/Button.h"

#include "ConnectBrowserUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UConnectBrowserUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void IPSelected(FString _IP, ESelectInfo::Type _SelectionType);

	UFUNCTION(BlueprintCallable)
	void Connect();

	UFUNCTION(BlueprintCallable)
	void IPComboDataInit();

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* IPCombo;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConnectButton;
private:
	UPROPERTY()
	FString IPAddress = "127.0.0.1";
	UPROPERTY()
	FString Port = "30001";
};
