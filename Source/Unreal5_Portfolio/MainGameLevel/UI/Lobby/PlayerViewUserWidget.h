// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerViewUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UPlayerViewUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* P0Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* P1Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* P2Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* P3Name;

	UPROPERTY(meta = (BindWidget))
	class UImage* P0Img;
	UPROPERTY(meta = (BindWidget))
	class UImage* P1Img;
	UPROPERTY(meta = (BindWidget))
	class UImage* P2Img;
	UPROPERTY(meta = (BindWidget))
	class UImage* P3Img;

public:
	UPlayerViewUserWidget();
	UPlayerViewUserWidget(const FObjectInitializer &ObjectInitializer);

	void NativeConstruct() override;
	//void NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(int _Order, FText _Name);

	UFUNCTION(BlueprintCallable)
	void SetPlayerView(int _Order, int _CharacterType);

	UFUNCTION(BlueprintCallable)
	void SetP0Name(FText _Name);

	UFUNCTION(BlueprintCallable)
	void SetP1Name(FText _Name);

	UFUNCTION(BlueprintCallable)
	void SetP2Name(FText _Name);

	UFUNCTION(BlueprintCallable)
	void SetP3Name(FText _Name);

private:
	UPROPERTY()
	class UMaterial* MT_ElyCapture;

	UPROPERTY()
	class UMaterial* MT_VanguardCapture;

	UPROPERTY()
	class UMaterial* MT_AlienSoldierCapture;

	UPROPERTY()
	class UMaterial* MT_CryptoCapture;

	UPROPERTY()
	TMap<int, class UMaterial*> MTCharacterType;
};
