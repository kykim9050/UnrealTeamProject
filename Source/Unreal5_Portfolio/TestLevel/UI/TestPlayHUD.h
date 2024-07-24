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
	TMap<EUserWidgetType, UUserWidget*> AllTestPlayWidgets;

public:
	UFUNCTION(BlueprintCallable)
	TMap<EUserWidgetType, UUserWidget*> GetAllTestPlayWidgets();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOn(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOff(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UISwitch(EUserWidgetType _Type);
};
