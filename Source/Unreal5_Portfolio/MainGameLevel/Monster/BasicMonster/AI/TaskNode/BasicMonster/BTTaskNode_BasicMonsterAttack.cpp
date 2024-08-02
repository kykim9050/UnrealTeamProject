// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterAttack.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
#include "MainGameLevel/Monster/Animation/MonsterRandomAnimInstance.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Player/MainCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

#include "TestLevel/Character/TestCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Monster->ChangeRandomAnimation(EBasicMonsterAnim::Attack);
	MonsterData->TimeCount = Monster->GetAnimInstance()->GetKeyAnimMontage(EBasicMonsterAnim::Attack, Monster->GetAnimIndex())->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	// Target Check
	ATestCharacter* Target = GetValueAsObject<ATestCharacter>(OwnerComp, TEXT("TargetActor"));
	if (nullptr == Target)
	{
		StateChange(OwnerComp, EBasicMonsterState::Idle);
		return;
	}

	// Player Dead Check
	ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(Target->GetPlayerState());
	if (0.0f >= TargetPlayerState->GetPlayerHp())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		StateChange(OwnerComp, EBasicMonsterState::Idle);
		return;
	}

	//// Target Check
	//AMainCharacter* Target = GetValueAsObject<AMainCharacter>(OwnerComp, TEXT("TargetActor"));
	//if (nullptr == Target)
	//{
	//	StateChange(OwnerComp, EBasicMonsterState::Idle);
	//	return;
	//}
	//
	//// Player Dead Check
	//AMainPlayerState* TargetPlayerState = Cast<AMainPlayerState>(Target->GetPlayerState());
	//if (0.0f >= TargetPlayerState->GetPlayerHp())
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
	//	StateChange(OwnerComp, EBasicMonsterState::Idle);
	//	return;
	//}

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	UBasicMonsterData* MonsterData = Monster->GetSettingData();

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetPlayerLocation = Target->GetActorLocation();
	
	if (0.0f >= MonsterData->TimeCount)
	{
		StateChange(OwnerComp, EBasicMonsterState::Chase);
		return;
	}

	MonsterData->TimeCount -= DeltaSeconds;
}
