// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/AI/BTTaskNode_ClimbZombieClimb.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombie.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_ClimbZombieClimb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AClimbZombie* ClimbZombie = GetSelfActor<AClimbZombie>(OwnerComp);
	if (false == ClimbZombie->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("ClimbZombie Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ClimbZombie->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
	ClimbZombie->GetCharacterMovement()->MaxFlySpeed = ClimbZombie->GetSettingData()->ClimbSpeed;
	ClimbZombie->ChangeRandomAnimation(EBasicMonsterAnim::Climb);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_ClimbZombieClimb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AClimbZombie* ClimbZombie = GetSelfActor<AClimbZombie>(OwnerComp);
	FVector DestPos = GetValueAsVector(OwnerComp, TEXT("Destination"));
	FVector CurPos = ClimbZombie->GetActorLocation();

	//if (CurPos.Z >= Dest.Z - (ClimbZombie->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 1.5f))
	if (CurPos.Z >= DestPos.Z)
	{
		StateChange(OwnerComp, EBasicMonsterState::ClimbEnd);
		return;
	}
}