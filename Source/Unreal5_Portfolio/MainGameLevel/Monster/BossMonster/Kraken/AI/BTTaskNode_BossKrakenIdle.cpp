// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/AI/BTTaskNode_BossKrakenIdle.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"

#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossKrakenIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	if (false == Kraken->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossKrakenData* KrakenData = Kraken->GetSettingData();
	KrakenData->TimeCount = IdleTime;
	Kraken->ChangeAnimation(EBossMonsterAnim::Idle);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossKrakenIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UBossMonsterData* KrakenData = GetSelfActor<ABossKraken>(OwnerComp)->GetSettingData();

	if (0.0f >= KrakenData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Chase);
		return;
	}

	KrakenData->TimeCount -= DeltaSeconds;
}
