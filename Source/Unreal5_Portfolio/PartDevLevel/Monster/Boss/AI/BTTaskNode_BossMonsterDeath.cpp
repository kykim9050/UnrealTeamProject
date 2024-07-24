// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonsterDeath.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

#include "Global/DataTable/BossDataRow.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossMonsterDeath::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	if (false == BossMonster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("BossMonster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));

	BossMonster->ChangeAniValue(EBossMonsterAnim::Dead);
	BossMonster->SetLifeSpan(5.0f);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossMonsterDeath::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
