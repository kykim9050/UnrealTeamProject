// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/AI/BTTaskNode_BossHeartChase.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossHeartChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	if (false == Heart->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Heart Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossHeartData* HeartData = Heart->GetSettingData();
	if (false == HeartData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("HeartData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Heart->GetCharacterMovement()->MaxWalkSpeed = HeartData->BaseData->ChaseSpeed;
	Heart->ChangeAnimation(EBossMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossHeartChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	FVector HeartLocation = Heart->GetActorLocation();

	AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	// 공격 범위 안에 있으면 MeleeAttack
	UBossHeartData* HeartData = Heart->GetSettingData();
	FVector LocationDiff = TargetLocation - HeartLocation;
	float DiffLength = LocationDiff.Size();
	if (DiffLength <= HeartData->BaseData->MeleeAttackRange)
	{
		StateChange(OwnerComp, EBossMonsterState::MeleeAttack);
		return;
	}

	// 이동
	Heart->GetAIController()->MoveToLocation(TargetLocation);
}
