// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterIdle.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "Global/DataTable/MonsterDataRow.h"


EBTNodeResult::Type UBTTaskNode_MonsterIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

    ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
    if (false == Monster->IsValidLowLevel())
    {
        UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
        return EBTNodeResult::Type::Aborted;
    }

    return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

    UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
    AMainGameState* GameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
    UActorGroup* Players = GameState->GetActorGroup(EObjectType::Player);

    // 플레이어 존재 확인
    if (true == Players->Actors.IsEmpty())
    {
        //FinishLatentTask(_OwnerComp, EBTNodeResult::Aborted);
        //return;
    }

    MonsterData->IdleTime += _DeltaSeconds;
    if (2.0f < MonsterData->IdleTime)
    {
        MonsterData->IdleTime = 0.0f;
        StateChange(_OwnerComp, EMonsterState::Patrol); 
        return;
    }
}