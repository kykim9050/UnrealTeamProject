// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestBrowserUserWidget.generated.h"

/**
 * 
 */
class UComboBoxString;
UCLASS()
class UNREAL5_PORTFOLIO_API UTestBrowserUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ServerStart();
	UFUNCTION(BlueprintCallable)
	void Connect(FString _IP);
	UFUNCTION(BlueprintCallable)
	void ServerInitialize(FName _IPName);

	// IP ComboBox 관련 함수
	UFUNCTION(BlueprintCallable)
	void IPComboDataInit(UDataTable* _IPData, UComboBoxString* _Combo);
	UFUNCTION(BlueprintCallable)
	void IPComboSelectChange(FString _Text);

private:
	FString IPAddress = "127.0.0.1";
	FString Port = "30001";
};
