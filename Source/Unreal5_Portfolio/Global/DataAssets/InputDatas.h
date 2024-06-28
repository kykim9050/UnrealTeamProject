// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputDatas.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UInputDatas : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UInputDatas();
	~UInputDatas();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UInputAction*> Actions;
};