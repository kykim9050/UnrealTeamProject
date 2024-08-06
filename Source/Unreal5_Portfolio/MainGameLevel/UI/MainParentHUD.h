// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalHUD.h"
#include "Global/ContentsEnum.h"
#include "Global/DataTable/WidgetDataRow.h"
#include "MainParentHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainParentHUD : public AGlobalHUD
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;

	virtual void AllUISetting();

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMainGameInstance* Inst = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EUserWidgetType, UUserWidget*> AllWidgets;

public:
	UFUNCTION(BlueprintCallable)
	TMap<EUserWidgetType, UUserWidget*> GetAllWidgets();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOn(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOff(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	void UISwitch(EUserWidgetType _Type);

	UFUNCTION(BlueprintCallable)
	virtual void AllUIOff();

	UFUNCTION(BlueprintCallable)
	virtual void AllUIOn();
};
