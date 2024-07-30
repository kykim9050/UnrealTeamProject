// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_MonsterScream.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UMyBTTaskNode_MonsterScream::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	Monster->ChangeRandomAnimation(ETestMonsterAnim::Scream);
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::Scream, Monster->GetAniIndex())->GetPlayLength();

	return EBTNodeResult::InProgress;
}

void UMyBTTaskNode_MonsterScream::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));

	if (ETestMonsterState::Scream != static_cast<ETestMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}

	FVector CurMonsterPos = Monster->GetActorLocation();
	CurMonsterPos.Z = 0.0f;
	FVector TargetPos = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"))->GetActorLocation();
	TargetPos.Z = 0.0f;
	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(CurMonsterPos, TargetPos);
	Monster->SetActorRotation(TurnRot);

	if (0.0f >= MonsterData->AnimationTime)
	{
		StateChange(_OwnerComp, ETestMonsterState::Chase);
		return;
	}

	MonsterData->AnimationTime -= _DeltaSeconds;
}
