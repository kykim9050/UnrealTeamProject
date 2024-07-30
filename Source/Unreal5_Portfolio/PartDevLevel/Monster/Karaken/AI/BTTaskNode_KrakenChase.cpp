// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Karaken/AI/BTTaskNode_KrakenChase.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UBTTaskNode_KrakenChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ETestMonsterState CurState = static_cast<ETestMonsterState>(GetCurState(OwnerComp));
	if (ETestMonsterState::Chase != CurState)
	{
		LOG(MonsterLog, Fatal, TEXT("Monster State Is Not Chase"));
		return EBTNodeResult::Type::Aborted;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (nullptr == Target)
	{
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return EBTNodeResult::Type::Succeeded;
	}

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(OwnerComp, TEXT("MonsterData"));
	MonsterData->DestLoc = Target->GetActorLocation();

	Monster->ChangeRandomAnimation(ETestMonsterAnim::Run);
	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_KrakenChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(OwnerComp, TEXT("MonsterData"));

	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(MonsterData->DestLoc);

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	FVector LocationDiff = Target->GetActorLocation() - Monster->GetActorLocation();
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackBoundary)
	{
		StateChange(OwnerComp, ETestMonsterState::Attack);
		return;
	}

	if (IsMove == EPathFollowingRequestResult::Type::AlreadyAtGoal)
	{
		//StateChange(OwnerComp, ETestMonsterState::GroundAttack);
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return;
	}
}
