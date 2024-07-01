// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterPatrol.h"
#include "TestLevel/Monster/TestMonsterBaseAIController.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "Global/ContentsLog.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationData.h"

EBTNodeResult::Type UBTTaskNode_MonsterPatrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	
	// Find PatrolLocation
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	FNavLocation PatrolLocation(FVector::ZeroVector);
	bool IsFind = NavSystem->GetRandomReachablePointInRadius(MonsterData->OriginPos, MonsterData->Max_PatrolRange, PatrolLocation);
	
	if (false == IsFind)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	SetValueAsVector(_OwnerComp, "PatrolLocation", PatrolLocation.Location);

	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterData->Data->GetWalkSpeed();
	Monster->ChangeAnimation(EMonsterAnim::Walk);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterPatrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(GetValueAsVector(_OwnerComp, TEXT("PatrolLocation")));

	bool CanSee = _OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanSeePlayer"));
	if (true == CanSee)
	{
		StateChange(_OwnerComp, EMonsterState::Chase);
		return;
	}

	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == IsMove)
	{
		StateChange(_OwnerComp, EMonsterState::Idle);
		return;
	}
}
