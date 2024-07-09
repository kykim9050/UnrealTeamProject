// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterChase.h"

#include "TestLevel/Monster/TestMonsterBaseAIController.h"
#include "TestLevel/Monster/TestMonsterBase.h"

#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_MonsterChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> Monster Is Not Valid"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterData->Data->GetRunSpeed();
	Monster->ChangeAniValue(EMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(TargetActor->GetActorLocation());
	
	if (EMonsterState::Fall == static_cast<EMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 범위 안에 있으면 공격상태로 변경
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LocationDiff = TargetLocation - MonsterLocation;
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackBoundary)
	{
		StateChange(_OwnerComp, EMonsterState::Attack);
		return;
	}
}
