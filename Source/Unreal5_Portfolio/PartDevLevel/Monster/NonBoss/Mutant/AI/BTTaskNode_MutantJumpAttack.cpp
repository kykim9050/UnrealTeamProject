// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MutantJumpAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MutantJumpAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::JumpAttack, Monster->GetAniIndex())->GetPlayLength();

	AActor* Target = GetValueAsObject<AActor>(_OwnerComp, (TEXT("TargetActor")));
	if (nullptr == Target)
	{
		StateChange(_OwnerComp, ETestMonsterState::Idle);
		return EBTNodeResult::Failed;
	}

	Monster->ChangeRandomAnimation(ETestMonsterAnim::JumpAttack);
	MonsterData->AttackDamage = MonsterData->JumpAttackDamage;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MutantJumpAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(_OwnerComp, TEXT("MonsterData"));

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
			SetValueAsObject(_OwnerComp, TEXT("TargetActor"), nullptr);
			SetValueAsBool(_OwnerComp, TEXT("CanSeePlayer"), false);
			return;
		}
		else
		{
			FVector MonsterLocation = Monster->GetActorLocation();
			FVector TargetLocation = TargetActor->GetActorLocation();

			FVector LocationDiff = TargetLocation - MonsterLocation;
			float Dist = LocationDiff.Size();
			if (MonsterData->AttackRange >= Dist)
			{
				StateChange(_OwnerComp, ETestMonsterState::Attack);
				return;
			}
			else if (MonsterData->JumpAttackBoundary >= Dist)
			{
				MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::JumpAttack, Monster->GetAniIndex())->GetPlayLength();
				FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
				Monster->SetActorRotation(TurnRot);
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
