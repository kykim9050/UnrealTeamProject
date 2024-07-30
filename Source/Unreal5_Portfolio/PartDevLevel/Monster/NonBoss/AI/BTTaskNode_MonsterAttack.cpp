// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MonsterAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterBaseData* MonsterData = GetValueAsObject<UTestMonsterBaseData>(_OwnerComp, TEXT("MonsterData"));
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Attack);
	MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Attack, Monster->GetAniIndex())->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UTestMonsterBaseData* MonsterData = GetValueAsObject<UTestMonsterBaseData>(_OwnerComp, TEXT("MonsterData"));

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
				MonsterData->AttackTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Attack, Monster->GetAniIndex())->GetPlayLength();
			}
			else
			{
				MonsterData->AttackTime = 0.0f;
				StateChange(_OwnerComp, ETestMonsterState::Chase);
				return;
			}
		}
	}

	MonsterData->AttackTime -= _DeltaSeconds;
}
