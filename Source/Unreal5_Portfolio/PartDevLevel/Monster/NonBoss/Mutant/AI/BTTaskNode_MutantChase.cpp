// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MutantChase.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MutantChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(_OwnerComp, TEXT("MonsterData"));
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_NavWalking;
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetBaseData()->GetRunSpeed();
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MutantChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (ETestMonsterState::Chase != static_cast<ETestMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();

	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(TargetLocation);

	// ���� �ȿ� ������ ���ݻ��·� ����
	FVector LocationDiff = TargetLocation - MonsterLocation;
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackRange)
	{
		StateChange(_OwnerComp, ETestMonsterState::Attack);
		return;
	}
	else if (DiffLength <= MonsterData->JumpAttackBoundary)
	{
		StateChange(_OwnerComp, ETestMonsterState::JumpAttack);
		return;
	}

}