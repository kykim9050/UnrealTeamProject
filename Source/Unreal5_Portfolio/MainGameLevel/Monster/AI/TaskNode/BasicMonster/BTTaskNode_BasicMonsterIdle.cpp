// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/TaskNode/BasicMonster/BTTaskNode_BasicMonsterIdle.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameState.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
    if (false == Monster->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
    if (false == MonsterData->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    MonsterData->IdleTime = 2.0f;
    Monster->ChangeRandomAnimation(EBasicMonsterAnim::Idle);

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

    // TargetActor 존재시 Chase 상태로
    AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
    if (nullptr != TargetActor)
    {
        StateChange(OwnerComp, EBasicMonsterState::Chase);
        return;
    }

    UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
    if (false == MonsterData->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
        return;
    }

    // IdleTime 이후 Patrol 상태로
    if (0.0f > MonsterData->IdleTime)
    {
        StateChange(OwnerComp, EBasicMonsterState::Patrol);
        return;
    }

    MonsterData->IdleTime -= DeltaSeconds;
}
