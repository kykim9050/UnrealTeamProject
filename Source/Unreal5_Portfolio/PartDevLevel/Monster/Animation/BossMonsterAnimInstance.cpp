// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/BossMonsterAnimInstance.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterAIControllerBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

void UBossMonsterAnimInstance::AnimNotify_RAttackEnd()
{
	ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(GetOwningActor());
	if (nullptr == BossMonster)
	{
		LOG(MonsterLog, Fatal, "BossMonster is nullptr");
		return;
	}

	if (false == BossMonster->HasAuthority())
	{
		return;
	}

	BossMonster->GetBossAIController()->GetBlackboardComponent()->SetValueAsEnum("State", static_cast<uint8>(EBossMonsterState::Chase));

}

void UBossMonsterAnimInstance::AnimNotify_MAttackEnd()
{
	ATestBossMonsterBase* BossMonster = Cast<ATestBossMonsterBase>(GetOwningActor());
	if (nullptr == BossMonster)
	{
		LOG(MonsterLog, Fatal, "BossMonster is nullptr");
		return;
	}

	if (false == BossMonster->HasAuthority())
	{
		return;
	}

	BossMonster->GetBossAIController()->GetBlackboardComponent()->SetValueAsEnum("State", static_cast<uint8>(EBossMonsterState::Chase));
}
