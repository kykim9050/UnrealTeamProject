// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicMonsterAIController.generated.h"



/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABasicMonsterAIController();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree = nullptr;

};
