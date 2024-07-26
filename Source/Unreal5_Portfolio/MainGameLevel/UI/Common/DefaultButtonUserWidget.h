// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "DefaultButtonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UDefaultButtonUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* DefaultButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText _text);

};
