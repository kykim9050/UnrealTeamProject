// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/AI/TaskNode/BTTaskNodeBase_BasicMonster.h"
#include "BTTaskNode_BasicMonsterClimbEnd.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BasicMonsterClimbEnd : public UBTTaskNodeBase_BasicMonster
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;

};
