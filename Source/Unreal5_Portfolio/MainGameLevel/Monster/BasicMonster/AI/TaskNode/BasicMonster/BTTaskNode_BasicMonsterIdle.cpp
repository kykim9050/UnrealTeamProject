// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterIdle.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"

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

    UBasicMonsterData* MonsterData = Monster->GetSettingData();
    if (false == MonsterData->IsValidLowLevel())
    {
        LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
        return EBTNodeResult::Type::Aborted;
    }

    Monster->ChangeRandomAnimation(EBasicMonsterAnim::Idle);
    MonsterData->TimeCount = IdleTime;

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);
    
    UBasicMonsterData* MonsterData = GetSelfActor<ABasicMonsterBase>(OwnerComp)->GetSettingData();

    // TargetActor 존재시 상태 변화
    AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
    if (nullptr != TargetActor)
    {
        switch (MonsterData->bScream)
        {
        case true:
            StateChange(OwnerComp, EBasicMonsterState::Scream);
            return;
        case false:
            StateChange(OwnerComp, EBasicMonsterState::Chase);
            return;
        }
    }

    // IdleTime 이후 Patrol 상태로
    if (0.0f > MonsterData->TimeCount)
    {
        StateChange(OwnerComp, EBasicMonsterState::Patrol);
        return;
    }

    MonsterData->TimeCount -= DeltaSeconds;
}
