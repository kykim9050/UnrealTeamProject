// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/TaskNode/BTTaskNode_BasicMonsterClimb.h"
#include "MainGameLevel/Monster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterClimb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
	Monster->GetCharacterMovement()->MaxFlySpeed = 200.0f;
	Monster->GetCapsuleComponent()->SetCapsuleRadius(50.0f);
	Monster->ChangeAniType(EBasicMonsterAnim::Climb);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMonsterClimb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);

	ABasicMonsterAIController* AIController = Monster->GetAIController();
	FVector Destination = AIController->GetBlackboardComponent()->GetValueAsVector("Destination");
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector ForwardVector = Monster->GetActorForwardVector();

	if (MonsterLocation.Z >= Destination.Z - Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())
	{
		Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		StateChange(OwnerComp, EBasicMonsterState::ClimbEnd);
		return;
	}
}
