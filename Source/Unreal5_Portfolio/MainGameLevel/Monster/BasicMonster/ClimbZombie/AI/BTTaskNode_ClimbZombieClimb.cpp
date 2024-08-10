// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/AI/BTTaskNode_ClimbZombieClimb.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombieData.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombie.h"

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

	if (CurPos.Z >= DestPos.Z)
	{
		StateChange(OwnerComp, EBasicMonsterState::ClimbEnd);
		return;
	}
}
