// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/SwitchObject.h"
#include "Bomb.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABomb : public ASwitchObject
{
	GENERATED_BODY()
	
public:

	void SetInfo(FName _InfoName);

protected:
	ABomb();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	void InterAction() override;

private:
	TSubclassOf<AActor> InteractObjClass = TSubclassOf<AActor>();

	bool BombStart = false;
};
