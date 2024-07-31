// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterIdle.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Data/BasicMonsterData.h"

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

    UBasicMonsterData* MonsterData = GetValueAsObject<UBasicMonsterData>(OwnerComp, TEXT("MonsterData"));
    if (false == MonsterData->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    MonsterData->TimeCount = IdleTime;
    Monster->ChangeRandomAnimation(EBasicMonsterAnim::Idle);

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

    // TargetActor ����� Chase ���·�
    AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
    if (nullptr != TargetActor)
    {
        StateChange(OwnerComp, EBasicMonsterState::Chase);
        return;
    }

    UBasicMonsterData* MonsterData = GetValueAsObject<UBasicMonsterData>(OwnerComp, TEXT("MonsterData"));
    if (false == MonsterData->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
        return;
    }

    // IdleTime ���� Patrol ���·�
    if (0.0f > MonsterData->TimeCount)
    {
        StateChange(OwnerComp, EBasicMonsterState::Patrol);
        return;
    }

    MonsterData->TimeCount -= DeltaSeconds;
}