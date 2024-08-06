// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABossMonsterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree = nullptr;
	
};
