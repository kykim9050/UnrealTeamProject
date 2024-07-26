// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "Bomb.generated.h"

/**
 * 
 */
enum class BombState
{
	Idle,
	Install,
	None,
};


UCLASS()
class UNREAL5_PORTFOLIO_API ABomb : public AMapObjectBase
{
	GENERATED_BODY()
	
public:

	void SetInfo(FName _InfoName);

	BombState CurBombState = BombState::Idle;

	UFUNCTION()
	void CharacterToDestroy();

protected:
	ABomb();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	void InterAction() override;

	void TimeFlow(float _DeltaTime);

private:
	TSubclassOf<AActor> InteractObjClass = TSubclassOf<AActor>();

	bool BombStart = false;

	float BombTime = 3.f;

};
