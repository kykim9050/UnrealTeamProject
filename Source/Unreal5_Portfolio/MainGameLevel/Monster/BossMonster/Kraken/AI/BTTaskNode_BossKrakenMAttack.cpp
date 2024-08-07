
// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/AI/BTTaskNode_BossKrakenMAttack.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossKrakenMAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Kraken->ChangeAnimation(EBossMonsterAnim::MeleeAttack);
	KrakenData->TimeCount = Kraken->GetAnimInstance()->GetKeyAnimMontage(EBossMonsterAnim::MeleeAttack)->GetPlayLength();
	KrakenData->AttackDamage = KrakenData->BaseData->MeleeAttackDamage;
	Kraken->GetAIController()->StopMovement();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossKrakenMAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UBossKrakenData* KrakenData = GetSelfActor<ABossKraken>(OwnerComp)->GetSettingData();

	if (0.0f >= KrakenData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Idle);
		return;
	}

	KrakenData->TimeCount -= DeltaSeconds;
}
