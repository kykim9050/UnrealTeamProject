// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public :
	AMainPlayerState();

	UFUNCTION()
	FORCEINLINE float GetPlayerHp() const
	{
		return PlayerHp;
	}



public :
	UFUNCTION()
	void InitPlayerData();



public :
	UPROPERTY()
	float PlayerHp = 0;
};
