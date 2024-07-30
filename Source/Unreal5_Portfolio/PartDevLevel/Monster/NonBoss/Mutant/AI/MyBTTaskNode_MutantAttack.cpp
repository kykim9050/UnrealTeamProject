// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_MutantAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UMyBTTaskNode_MutantAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	UTestMonsterBaseData* MonsterData = GetValueAsObject<UTestMonsterBaseData>(_OwnerComp, TEXT("MonsterData"));
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
	UTestMonsterBaseData* MonsterData = GetValueAsObject<UTestMonsterBaseData>(_OwnerComp, TEXT("MonsterData"));

	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}

	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
	Monster->SetActorRotation(TurnRot);

	if (0.0f >= MonsterData->AnimationTime)
	{
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
			FVector LocationDiff = TargetLocation - MonsterLocation;
			float Dist = LocationDiff.Size();
			if (MonsterData->AttackRange >= Dist)
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
