// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterAttack.h"

#include "Global/ContentsLog.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestLevel/Character/TestCharacter.h"

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
	Monster->ChangeAniValue(EMonsterAnim::Attack);

	Monster->ChangeAnimation(EMonsterAnim::Attack);
	Monster->SetActiveAttackCollision(true);
	MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::Attack))->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	FVector MyLoc = Monster->GetActorLocation();
	FVector TargetLoc = TargetActor->GetActorLocation();
	
	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MyLoc, TargetLoc);
	Monster->SetActorRotation(TurnRot);

	if (0.0f >= MonsterData->AttackTime)
	{
		ATestCharacter* TargetCharacter = Cast<ATestCharacter>(TargetActor);
		if (0.0f >= TargetCharacter->GetPlayerHp())
		{
			Monster->SetActiveAttackCollision(false);
			Monster->SetIsCharacterHit(false);
			StateChange(_OwnerComp, EMonsterState::Idle);
			_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			_OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), false);
			return;
		}
		else
		{
			if (true == Monster->GetIsCharacterHit())
			{
				TargetCharacter->GetDamage(Monster->GetAttackDamage());
				Monster->SetIsCharacterHit(false);
			}
			FVector TargetToMy = TargetLoc - MyLoc;
			float Dist = abs(TargetToMy.Length());
			if (MonsterData->AttackBoundary >= Dist)
			{
				MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::Attack))->GetPlayLength();
			}
			else
			{
				MonsterData->AttackTime = 0.0f;
				Monster->SetActiveAttackCollision(false);
				StateChange(_OwnerComp, EMonsterState::Chase);
				return;
			}
		}
	}
	MonsterData->AttackTime -= _DeltaSeconds;
}
