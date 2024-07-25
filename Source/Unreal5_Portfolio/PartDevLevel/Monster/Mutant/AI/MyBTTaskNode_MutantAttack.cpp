// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Mutant/AI/MyBTTaskNode_MutantAttack.h"

#include "Global/ContentsLog.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"
#include "Components/CapsuleComponent.h"


EBTNodeResult::Type UMyBTTaskNode_MutantAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Attack, Monster->GetAniIndex())->GetPlayLength();

	AActor* Target = Cast<AActor>(_OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (nullptr == Target)
	{
		StateChange(_OwnerComp, ETestMonsterState::Idle);
		return EBTNodeResult::Failed;
	}

	Monster->ChangeRandomAnimation(ETestMonsterAnim::Attack);
	return EBTNodeResult::InProgress;
}

void UMyBTTaskNode_MutantAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (ETestMonsterState::Attack != static_cast<ETestMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}

	if (0.0f >= MonsterData->AnimationTime)
	{
		AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
		ATestCharacter* TargetPlayer = Cast<ATestCharacter>(TargetActor);
		ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(TargetPlayer->GetPlayerState());

		if (0.0f >= TargetPlayerState->GetPlayerHp())
		{
			StateChange(_OwnerComp, ETestMonsterState::Idle);
			_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			_OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), false);
			return;
		}
		else
		{
			FVector MonsterLocation = Monster->GetActorLocation();
			FVector TargetLocation = TargetActor->GetActorLocation();

			FVector LocationDiff = TargetLocation - MonsterLocation;
			float Dist = LocationDiff.Size();
			if (MonsterData->AttackBoundary >= Dist)
			{
				MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Attack, Monster->GetAniIndex())->GetPlayLength();
				return;
			}
			else if (MonsterData->JumpAttackBoundary >= Dist)
			{
				
				StateChange(_OwnerComp, ETestMonsterState::JumpAttack);
				return;
			}
			else
			{
				StateChange(_OwnerComp, ETestMonsterState::Chase);
				return;
			}
		}
	}
	else
	{
		MonsterData->AnimationTime -= _DeltaSeconds;
	}
}