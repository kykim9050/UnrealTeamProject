// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/TaskNode/BTTaskNode_BasicMonsterAttack.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Player/MainCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
	if (false == MonsterData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->ChangeAniType(ETestMonsterAnim::Attack);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	// 플레이어 체크
	AMainCharacter* TargetPlayer = GetValueAsObject<AMainCharacter>(OwnerComp, TEXT("TargetActor"));
	if (nullptr == TargetPlayer)
	{
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return;
	}

	// 사망한 플레이어일시 Idle
	AMainPlayerState* TargetPlayerState = Cast<AMainPlayerState>(TargetPlayer->GetPlayerState());
	if (0.0f >= TargetPlayerState->GetPlayerHp())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return;
	}

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetPlayerLocation = TargetPlayer->GetActorLocation();

	FVector LocationDiff = TargetPlayerLocation - MonsterLocation;
	float Distance = LocationDiff.Size();
	if (Distance >= MonsterData->AttackBoundary)
	{
		// 몬스터 회전
		FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetPlayerLocation);
		Monster->SetActorRotation(TurnRot);
	}
	else
	{
		StateChange(OwnerComp, ETestMonsterState::Chase);
		return;
	}
}
