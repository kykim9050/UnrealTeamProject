// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalHUD.h"
#include "Global/ContentsEnum.h"
#include "TestPlayHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestPlayHUD : public AGlobalHUD
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EInGameUIType, UUserWidget*> AllTestPlayWidgets;

public:
	UFUNCTION(BlueprintCallable)
	TMap<EInGameUIType, UUserWidget*> GetAllTestPlayWidgets();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(EInGameUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOn(EInGameUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOff(EInGameUIType _Type);
};
