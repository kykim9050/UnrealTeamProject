// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartDevLevel/Monster/NonBoss/AI/BTTaskNode_Monster.h"
#include "MyBTTaskNode_MutantAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMyBTTaskNode_MutantAttack : public UBTTaskNode_Monster
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
