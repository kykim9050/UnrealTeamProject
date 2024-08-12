// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLobbyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UPlayerLobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UDefaultButtonUserWidget* B_Ready;

	UPROPERTY(meta = (BindWidget))
	class UDefaultButtonUserWidget* B_Start;

	UPROPERTY(meta = (BindWidget))
	class UCharacterSelectionUserWidget* CharacterSelectionWindow;

	UFUNCTION(BlueprintCallable)
	void TravelToNext();

	UFUNCTION(BlueprintCallable)
	bool IsServer();

public:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnReadyBtn();

	UFUNCTION(BlueprintCallable)
	void OnStartBtn();

	UFUNCTION(BlueprintCallable)
	void ReadybtnVisibility(bool _On);

	UFUNCTION(BlueprintCallable)
	void StartbtnVisibility(bool _On);
};
