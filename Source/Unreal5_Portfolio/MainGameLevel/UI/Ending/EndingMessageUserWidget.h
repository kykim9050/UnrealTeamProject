// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingMessageUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UEndingMessageUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	FText EndingCreditText;

	UPROPERTY(BlueprintReadWrite)
	TArray<FText> EndingCreditArr;

	UFUNCTION(BlueprintCallable)
	void AddEndingCredit(FText _Text);

	UFUNCTION(BlueprintCallable)
	int GetCreditIndex()
	{
		return ++CreditIndex;
	}

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CreditIndex = -1;
};
