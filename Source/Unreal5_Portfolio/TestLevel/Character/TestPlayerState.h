// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
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

	UFUNCTION(Reliable, Server)
	void HealHp();
	void HealHp_Implementation();

	UFUNCTION(Reliable, Server)
	void AddDamage(float _Damage);
	void AddDamage_Implementation(float _Damage);

public:
	UFUNCTION()
	void InitPlayerData();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
private:
	UPROPERTY(Replicated)
	float PlayerHp = -1.0f;
};
