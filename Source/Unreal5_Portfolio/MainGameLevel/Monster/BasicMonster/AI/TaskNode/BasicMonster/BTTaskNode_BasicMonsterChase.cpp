// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterChase.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBasicMonsterData* MonsterData = Monster->GetSettingData();
	if (false == MonsterData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterData->BaseData->RunSpeed;
	Monster->ChangeRandomAnimation(EBasicMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	// 상태 변화시 Failed
	if (EBasicMonsterState::Chase != GetCurState<EBasicMonsterState>(OwnerComp))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();

	AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	// 공격 범위 안에 있으면 Attack
	UBasicMonsterData* MonsterData = Monster->GetSettingData();
	FVector LocationDiff = TargetLocation - MonsterLocation;
	float DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackRange)
	{
		StateChange(OwnerComp, EBasicMonsterState::Attack);
		return;
	}

	// 이동
	Monster->GetAIController()->MoveToLocation(TargetLocation);
}
