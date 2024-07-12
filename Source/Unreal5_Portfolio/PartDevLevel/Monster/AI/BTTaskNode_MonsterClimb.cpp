// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterClimb.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterClimb::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MonsterClimb::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
