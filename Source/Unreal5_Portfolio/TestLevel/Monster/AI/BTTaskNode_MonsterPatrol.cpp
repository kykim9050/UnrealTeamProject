// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterPatrol.h"

EBTNodeResult::Type UBTTaskNode_MonsterPatrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	return Result;
}

void UBTTaskNode_MonsterPatrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);


}
