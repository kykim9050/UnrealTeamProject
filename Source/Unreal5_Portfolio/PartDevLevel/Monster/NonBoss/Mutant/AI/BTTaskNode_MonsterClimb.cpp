// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MonsterClimb.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterClimb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
	Monster->GetCharacterMovement()->MaxFlySpeed = 200.0f;
	Monster->GetCapsuleComponent()->SetCapsuleRadius(60.0f);
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Climb);
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MonsterClimb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
	FVector Dest = GetValueAsVector(OwnerComp, TEXT("DestinationLocation"));
	FVector CurPos = Monster->GetActorLocation();

	if (CurPos.Z >= Dest.Z - (Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 1.5f))
	{
		Monster->GetCapsuleComponent()->SetCapsuleRadius(34.0f);
		//Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		StateChange(OwnerComp, ETestMonsterState::ClimbEnd);
		return;
	}

	Monster->AddMovementInput(Monster->GetActorForwardVector(), 20.0f);
	Monster->AddMovementInput(Monster->GetActorUpVector(), 20.0f);

	
	
}
