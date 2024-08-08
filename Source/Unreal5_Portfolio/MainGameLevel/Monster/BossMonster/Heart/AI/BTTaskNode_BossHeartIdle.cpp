// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/AI/BTTaskNode_BossHeartIdle.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossHeartIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	if (false == Heart->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Heart Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossHeartData* HeartData = Heart->GetSettingData();
	if (false == HeartData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("HeartData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	HeartData->TimeCount = IdleTime;
	Heart->ChangeAnimation(EBossMonsterAnim::Idle);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossHeartIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UBossHeartData* HeartData = GetSelfActor<ABossHeart>(OwnerComp)->GetSettingData();
	if (0.0f >= HeartData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Walk);
		return;
	}

	HeartData->TimeCount -= DeltaSeconds;
}
