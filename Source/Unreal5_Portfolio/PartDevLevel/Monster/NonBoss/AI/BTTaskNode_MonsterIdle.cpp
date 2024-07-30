// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MonsterIdle.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

    ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
    if (false == Monster->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
    MonsterData->IdleTime = 0.0f;

    Monster->ChangeRandomAnimation(ETestMonsterAnim::Idle);

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

    UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));

    bool CanSee = _OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanSeePlayer"));
    if (true == CanSee)
    {
        ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
        ETestMonsterType MonsterType = Monster->GetBaseData()->GetMonsterType();
        ETestMonsterState NextState;
        switch (MonsterType)
        {
        case ETestMonsterType::Noraml:
            NextState = ETestMonsterState::Chase;
            break;
        case ETestMonsterType::Crawl:
            NextState = ETestMonsterState::Scream;
            break;
        }
        StateChange(_OwnerComp, NextState);
        return;
    }

    if (2.0f < MonsterData->IdleTime)
    {
        StateChange(_OwnerComp, ETestMonsterState::Patrol); 
        return;
    }

    MonsterData->IdleTime += _DeltaSeconds;
}