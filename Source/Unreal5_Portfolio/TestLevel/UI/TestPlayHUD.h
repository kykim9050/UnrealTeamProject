// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalHUD.h"
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
	TMap<FString, UUserWidget*> AllTestPlayWidgets;
};
