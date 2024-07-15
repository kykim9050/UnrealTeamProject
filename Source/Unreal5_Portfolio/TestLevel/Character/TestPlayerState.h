// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATestPlayerState();

	UFUNCTION()
	FORCEINLINE float GetPlayerHp() const
	{
		return PlayerHp;
	}

	UFUNCTION()
	FORCEINLINE float GetPlayerNumber() const
	{
		return PlayerNumber;
	}

public:
	UFUNCTION()
	void InitPlayerData();

public:
	UPROPERTY()
	float PlayerHp = 0;

	UPROPERTY()
	int PlayerNumber = -1; // 내가 몇 번째 플레이어인지
};
