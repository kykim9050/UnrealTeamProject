// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossMonsterBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ABossMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABossMonsterBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Data
	//virtual void InitData(const FMonsterDataRow* BaseData) {};

private:



};
