// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "BasicMutant.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMutant : public ABasicMonsterBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
