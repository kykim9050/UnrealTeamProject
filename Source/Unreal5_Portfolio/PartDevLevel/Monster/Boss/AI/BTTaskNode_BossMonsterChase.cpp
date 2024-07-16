// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonsterChase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterAIControllerBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

#include "TestLevel/Character/TestCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossMonsterChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	if (false == BossMonster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> BossMonster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));
	BossMonster->GetCharacterMovement()->MaxWalkSpeed = BossData->Data->GetRunSpeed();
	BossMonster->ChangeAniValue(EBossMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossMonsterChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (EBossMonsterState::Chase != static_cast<EBossMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));
	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	FVector MonsterLocation = BossMonster->GetActorLocation();

	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	EPathFollowingRequestResult::Type IsMove = BossMonster->GetBossAIController()->MoveToLocation(TargetLocation);

	// 범위 안에 있으면 공격상태로 변경
	FVector LocationDiff = TargetLocation - MonsterLocation;
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= BossData->Data->GetMeleeAttackBoundary())
	{
		StateChange(_OwnerComp, EBossMonsterState::MeleeAttack);
		return;
	}
}