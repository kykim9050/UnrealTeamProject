// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void Damaged(float Damage) {};

};
