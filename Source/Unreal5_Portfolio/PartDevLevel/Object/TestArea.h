// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "TestArea.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestArea : public AMapObjectBase
{
	GENERATED_BODY()
	
public:

	ATestArea();



protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void InterAction() override;


	UPROPERTY(EditAnywhere)
	class UBoxComponent* SetBombBox;


private:

	ABomb* HaveBomb = nullptr;

	void SetBomb();

	void TimeFlow(float _DeltaTime);


	float SetBombTime = 0.f;
	float BombTime = 30.f;


	bool IsBomb = false;

	

};
