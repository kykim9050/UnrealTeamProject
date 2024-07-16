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

	UFUNCTION()
	FORCEINLINE TArray<ATestPlayerState*> GetAllPlayerStates() const
	{
		return AllPlayerStates;
	}

	UFUNCTION()
	void SetPlayerHp(float _Hp);
	UFUNCTION()
	void SetPlayerNumber(int _Num);
	UFUNCTION()
	void SetAllPlayerStates(TArray<ATestPlayerState*> _Arr);

	UFUNCTION()
	void AddDamage(float _Damage);
public:
	UFUNCTION()
	void InitPlayerData(int _PlayerNumber);

private:
	UPROPERTY()
	float PlayerHp = 0;

	UPROPERTY()
	int PlayerNumber = -1;	// 내가 몇 번째 플레이어인지

	TArray<ATestPlayerState*> AllPlayerStates; // 모든 플레이어의 State
};
