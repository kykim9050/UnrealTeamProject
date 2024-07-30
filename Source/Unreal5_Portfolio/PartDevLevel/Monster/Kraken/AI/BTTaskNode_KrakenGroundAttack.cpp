// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Kraken/AI/BTTaskNode_KrakenGroundAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_KrakenGroundAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ETestMonsterState CurState = static_cast<ETestMonsterState>(GetCurState(OwnerComp));
	if (ETestMonsterState::GroundAttack != CurState)
	{
		LOG(MonsterLog, Fatal, TEXT("Monster State Is Not GroundAttack"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(OwnerComp, TEXT("MonsterData"));
	MonsterData->IsGroundAttack = false;

	Monster->ChangeRandomAnimation(ETestMonsterAnim::Attack);
	MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Attack, Monster->GetAniIndex())->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_KrakenGroundAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);
	
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(OwnerComp, TEXT("MonsterData"));
	if (0.0f >= MonsterData->AnimationTime)
	{
		Monster->SpawnRock();
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return;
	}
	else
	{
		MonsterData->AnimationTime -= DeltaSeconds;
	}
}
