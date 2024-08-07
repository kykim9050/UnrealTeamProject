// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/AI/BTTaskNode_BossKrakenRAttack.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossKrakenRAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	if (false == Kraken->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Kraken Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossKrakenData* KrakenData = Kraken->GetSettingData();
	if (false == KrakenData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("KrakenData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Kraken->ChangeAnimation(EBossMonsterAnim::RangedAttack);
	KrakenData->TimeCount = Kraken->GetAnimInstance()->GetKeyAnimMontage(EBossMonsterAnim::RangedAttack)->GetPlayLength();
	Kraken->GetAIController()->StopMovement();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossKrakenRAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	UBossKrakenData* KrakenData = Kraken->GetSettingData();
	
	if (0.0f >= KrakenData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Idle);
		return;
	}
	
	KrakenData->TimeCount -= DeltaSeconds;
}
