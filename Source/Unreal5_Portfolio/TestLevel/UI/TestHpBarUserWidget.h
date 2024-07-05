// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestHpBarUserWidget.generated.h"

/**
 * 
 */
class UMainGameInstance;
class ATestCharacter;
UCLASS()
class UNREAL5_PORTFOLIO_API UTestHpBarUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

public:
	void NativeConstruct();
	void NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime);

	UFUNCTION(BlueprintCallable)
	float HPUpdate();

	UMainGameInstance* Inst;
	ATestCharacter* MyCharacter;
	float CurHp;
	float MaxHp;
};
