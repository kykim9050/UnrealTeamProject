// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "ServerBtnUserWidget.generated.h"

/**
 * 
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);

UCLASS()
class UNREAL5_PORTFOLIO_API UServerBtnUserWidget : public UUserWidget
{
	GENERATED_BODY()

	//DECLARE_EVENT(UServerBtnUserWidget, FOnButtonClickedEvent)

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConnectButton;

public:
	void NativeConstruct() override;

	UFUNCTION()
	void OnServerButtonClicked();

	UFUNCTION()
	void OnConnectButtonClicked();

private:
	UPROPERTY()
	class AMainTitleHUD* TitleHUD = nullptr;

	UPROPERTY()
	FString Port = "30001";
};