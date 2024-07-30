// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHpbarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBossHpbarUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime) override;


	// 困连 备己夸家 
	UPROPERTY(meta = (BindWidget))
	class UImage* HpCaseImage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HpProgress;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BossNameBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BossHpText;

	UFUNCTION(Blueprintcallable)
	void SetHp(float _CurHp, float _MaxHp);
	UFUNCTION(Blueprintcallable)
	void SetBossName(FText _name);
};
