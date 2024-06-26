// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_MonsterIdle.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_MonsterIdle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
	
};























// ²¥ ºÎ²ô·¯
