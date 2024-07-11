// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GlobalHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AGlobalHUD : public AHUD
{
	GENERATED_BODY()
	
public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	void AddDebugString(FString _Text);
#endif

protected:
	void BeginPlay() override;

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DebugWidgetClass = TSubclassOf<UUserWidget>();

	UPROPERTY(EditAnywhere)
	class UTextDebugWidget* TextDebugWidget = nullptr;

#endif

};
