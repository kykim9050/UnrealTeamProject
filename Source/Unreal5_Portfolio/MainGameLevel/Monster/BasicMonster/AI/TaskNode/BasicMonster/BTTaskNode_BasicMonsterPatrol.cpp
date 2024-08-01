// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterPatrol.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	// Find PatrolLocation
	UBasicMonsterData* MonsterData = Monster->GetSettingData();
	if (false == MonsterData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	FNavLocation PatrolLocation(FVector::ZeroVector);
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	bool IsFind = NavSystem->GetRandomReachablePointInRadius(MonsterData->OriginPos, MonsterData->PatrolRange, PatrolLocation);
	if (false == IsFind)
	{
		return EBTNodeResult::Type::Failed;
	}

	SetValueAsVector(OwnerComp, TEXT("Destination"), PatrolLocation.Location);
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetSettingData()->BaseData->WalkSpeed;
	Monster->ChangeRandomAnimation(EBasicMonsterAnim::Walk);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);

	// TargetActor 존재시 상태 변화
	AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	if (nullptr != TargetActor)
	{
		switch (Monster->GetSettingData()->bScream)
		{
		case true:
			StateChange(OwnerComp, EBasicMonsterState::Scream);
			return;
		case false:
			StateChange(OwnerComp, EBasicMonsterState::Chase);
			return;
		}
	}

	// 목적지 도달 시 Idle
	FVector PatrolLocation = GetValueAsVector(OwnerComp, TEXT("Destination"));
	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(PatrolLocation);
	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == IsMove)
	{
		StateChange(OwnerComp, EBasicMonsterState::Idle);
		return;
	}
}
