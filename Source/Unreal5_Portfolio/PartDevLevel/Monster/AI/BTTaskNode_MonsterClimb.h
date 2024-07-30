// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartDevLevel/Monster/AI/BTTaskNode_Monster.h"
#include "BTTaskNode_MonsterClimb.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_MonsterClimb : public UBTTaskNode_Monster
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;

};
