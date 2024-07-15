// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterAttack.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"
#include "Kismet/KismetMathLibrary.h"

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
	MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::Attack))->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	
	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
	Monster->SetActorRotation(TurnRot);

	if (0.0f >= MonsterData->AttackTime)
	{
		ATestCharacter* TargetPlayer = Cast<ATestCharacter>(TargetActor);
		ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(TargetPlayer->GetPlayerState());

		if (0.0f >= TargetPlayerState->GetPlayerHp())
		{
			StateChange(_OwnerComp, EMonsterState::Idle);
			_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			_OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), false);
			return;
		}
		else
		{
			FVector LocationDiff = TargetLocation - MonsterLocation;
			float Dist = LocationDiff.Size();
			if (MonsterData->AttackBoundary >= Dist)
			{
				MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::Attack))->GetPlayLength();
			}
			else
			{
				MonsterData->AttackTime = 0.0f;
				StateChange(_OwnerComp, EMonsterState::Chase);
				return;
			}
		}
	}

	MonsterData->AttackTime -= _DeltaSeconds;
}
