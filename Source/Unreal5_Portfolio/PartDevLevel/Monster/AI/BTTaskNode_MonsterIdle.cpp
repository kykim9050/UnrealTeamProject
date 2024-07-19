// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterIdle.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTaskNode_MonsterIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

    ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
    if (false == Monster->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
    MonsterData->IdleTime = 0.0f;

    Monster->ChangeRandomAnimation(ETestMonsterAnim::Idle);

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

    UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

    bool CanSee = _OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanSeePlayer"));
    if (true == CanSee)
    {
        StateChange(_OwnerComp, ETestMonsterState::Chase);
        return;
    }

    if (2.0f < MonsterData->IdleTime)
    {
        StateChange(_OwnerComp, ETestMonsterState::Patrol); 
        return;
    }

    MonsterData->IdleTime += _DeltaSeconds;
}