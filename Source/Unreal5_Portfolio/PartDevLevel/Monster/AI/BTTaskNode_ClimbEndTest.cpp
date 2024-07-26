// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_ClimbEndTest.h"

#include "Global/ContentsLog.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_ClimbEndTest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, "Monster Is Not Valid");
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, "MonsterData");
	if (false == MonsterData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, "MonsterData Is Not Valid");
		return EBTNodeResult::Type::Aborted;
	}

	MonsterData->ClimbTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::ClimbEnd, Monster->GetAniIndex())->GetPlayLength();
	Monster->ChangeRandomAnimation(EBasicMonsterAnim::ClimbEnd);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_ClimbEndTest::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	if (ETestMonsterState::ClimbEnd != static_cast<ETestMonsterState>(GetCurState(OwnerComp)))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));

	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}

	if (0.0f >= MonsterData->ClimbTime)
	{
		/*FVector DestLoc = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("DestinationLocation"));
		DestLoc.Z += Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
		Monster->SetActorLocation(DestLoc);*/
		Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
		//Monster->ChangeRandomAnimation(EBasicMonsterAnim::Idle);
		StateChange(OwnerComp, ETestMonsterState::Chase);
		return;
	}
	else
	{
		MonsterData->ClimbTime -= DeltaSeconds;
	}
}