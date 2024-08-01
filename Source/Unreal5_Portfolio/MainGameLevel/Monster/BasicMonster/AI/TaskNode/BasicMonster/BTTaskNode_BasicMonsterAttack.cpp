// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterAttack.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
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

	UBasicMonsterData* MonsterData = GetValueAsObject<UBasicMonsterData>(OwnerComp, TEXT("MonsterData"));
	if (false == MonsterData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MonsterData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->ChangeRandomAnimation(EBasicMonsterAnim::Attack);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	// 플레이어 체크
	AMainCharacter* TargetPlayer = GetValueAsObject<AMainCharacter>(OwnerComp, TEXT("TargetActor"));
	if (nullptr == TargetPlayer)
	{
		StateChange(OwnerComp, EBasicMonsterState::Idle);
		return;
	}

	// 사망한 플레이어일시 Idle
	AMainPlayerState* TargetPlayerState = Cast<AMainPlayerState>(TargetPlayer->GetPlayerState());
	if (0.0f >= TargetPlayerState->GetPlayerHp())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		StateChange(OwnerComp, EBasicMonsterState::Idle);
		return;
	}

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	UBasicMonsterData* MonsterData = GetValueAsObject<UBasicMonsterData>(OwnerComp, TEXT("MonsterData"));

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetPlayerLocation = TargetPlayer->GetActorLocation();

	// 공격 범위 체크
	FVector LocationDiff = TargetPlayerLocation - MonsterLocation;
	float Distance = LocationDiff.Size();
	if (Distance <= MonsterData->AttackRange)
	{
		MonsterLocation.Z = 0.0f;
		TargetPlayerLocation.Z = 0.0f;

		FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetPlayerLocation);
		Monster->SetActorRotation(TurnRot);
	}
	else
	{
		StateChange(OwnerComp, EBasicMonsterState::Chase);
		return;
	}
}
