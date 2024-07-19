// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MonsterDevMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMonsterDevMode : public AGameMode
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void PostLogin(APlayerController* NewPlayer) override; // 플레이어 성공적인 입장(Login) 후 호출되는 함수 
	
};
