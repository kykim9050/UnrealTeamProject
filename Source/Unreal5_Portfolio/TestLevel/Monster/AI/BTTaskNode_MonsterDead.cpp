// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterDead.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

EBTNodeResult::Type UBTTaskNode_MonsterDead::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->ChangeAnimation(EMonsterAnim::Dead);
	Monster->GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel5);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterDead::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _NodeMemory, _DeltaSeconds);
}
