// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterAttack.h"

#include "Global/ContentsLog.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "Global/Animation/MainAnimInstance.h"

EBTNodeResult::Type UBTTaskNode_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->IdleTime = 0.0f;
	Monster->ChangeAnimation(EMonsterAnim::Attack);
	//Monster->Attack();

	MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::Attack))->GetPlayLength();
	AttackTime = MonsterData->AttackTime;

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (0.0f >= AttackTime)
	{
		AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
		/*if (0.0f >= TargetActor->GetHp())
		{
			StateChange(_OwnerComp, EMonsterState::Idle);
			_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("CanSeePlayer"), false);
			return;
		}
		else*/
		{
			FVector MyLoc = Monster->GetActorLocation();
			FVector TargetLoc = TargetActor->GetActorLocation();
			FVector MyToTarget = MyLoc - TargetLoc;
			float Dist = abs(MyToTarget.Length());
			if (MonsterData->AttackBoundary >= Dist)
			{
				AttackTime = MonsterData->AttackTime;
			}
			else
			{
				AttackTime = 0.0f;
				StateChange(_OwnerComp, EMonsterState::Chase);
				return;
			}
		}
	}
	AttackTime -= _DeltaSeconds;
}
