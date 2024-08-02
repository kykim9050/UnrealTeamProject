// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UCharacterSelectionUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int SelectedCharacter = -1;

public:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetSelectedCharacter(int _Num);

private:
	UPROPERTY()
	TMap<int, FName> CharTypeName;
};
