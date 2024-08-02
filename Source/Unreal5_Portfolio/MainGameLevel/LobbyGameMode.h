// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION()
	int GetPlayerCount()
	{
		return PlayerCount;
	}

	UFUNCTION()
	void SetPlayerCount(int _cnt)
	{
		PlayerCount = _cnt;
	}
	
	UFUNCTION()
	int GetReadyCount()
	{
		return ReadyCount;
	}

	UFUNCTION()
	void SetReadyCount(int _cnt)
	{
		ReadyCount = _cnt;
	}

	UFUNCTION(BlueprintCallable)
	void ListenServerOn();

private:
	UPROPERTY()
	int PlayerCount = 0;

	UPROPERTY()
	int ReadyCount = 0;

};
