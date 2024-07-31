// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/BasicMonster/AI/TaskNode/BTTaskNodeBase_Monster.h"
#include "BTTaskNode_BasicMonsterFall.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BasicMonsterFall : public UBTTaskNodeBase_BasicMonster
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;
	
};