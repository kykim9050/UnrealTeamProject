// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterIdle.h"

EBTNodeResult::Type UBTTaskNode_MonsterIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

    return Result;
}

void UBTTaskNode_MonsterIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

}