// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MonsterPatrol.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationData.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterPatrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(_OwnerComp, TEXT("MonsterData"));
	
	// Find PatrolLocation
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	FNavLocation PatrolLocation(FVector::ZeroVector);
	bool IsFind = NavSystem->GetRandomReachablePointInRadius(MonsterData->OriginPos, MonsterData->Max_PatrolRange, PatrolLocation);
	
	if (false == IsFind)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	SetValueAsVector(_OwnerComp, "DestinationLocation", PatrolLocation.Location);
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetBaseData()->WalkSpeed;
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Walk);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterPatrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector PatrolLocation = GetValueAsVector(_OwnerComp, TEXT("DestinationLocation"));
	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(PatrolLocation);

	bool CanSee = GetValueAsBool(_OwnerComp, TEXT("CanSeePlayer"));
	if (true == CanSee)
	{
		ETestMonsterType MonsterType = Monster->GetBaseData()->MonsterType;
		ETestMonsterState NextState;
		switch (MonsterType)
		{
		case ETestMonsterType::Noraml:
			NextState = ETestMonsterState::Chase;
			break;
		case ETestMonsterType::Crawl:
			NextState = ETestMonsterState::Scream;
			break;
		}
		StateChange(_OwnerComp, NextState);
		return;
	}

	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == IsMove)
	{
		StateChange(_OwnerComp, ETestMonsterState::Idle);
		return;
	}
}
