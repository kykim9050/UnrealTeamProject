// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CharacterDevMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ACharacterDevMode : public AGameMode
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	
};
