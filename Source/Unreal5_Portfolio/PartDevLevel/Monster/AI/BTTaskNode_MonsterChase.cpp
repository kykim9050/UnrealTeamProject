// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterChase.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetBaseData()->GetRunSpeed();
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	if (ETestMonsterState::Chase != static_cast<ETestMonsterState>(GetCurState(OwnerComp)))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();
	
	AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(TargetLocation);

	// 범위 안에 있으면 공격상태로 변경
	FVector LocationDiff = TargetLocation - MonsterLocation;
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackBoundary)
	{
		StateChange(OwnerComp, ETestMonsterState::Attack);
		return;
	}
}
