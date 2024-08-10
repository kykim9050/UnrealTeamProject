// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/AI/BTTaskNode_ClimbZombieClimbEnd.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombie.h"
#include "MainGameLevel/Monster/BasicMonster/ClimbZombie/ClimbZombieData.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/Animation/MonsterRandomAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_ClimbZombieClimbEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AClimbZombie* ClimbZombie = GetSelfActor<AClimbZombie>(OwnerComp);
	if (false == ClimbZombie->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("ClimbZombie Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	UClimbZombieData* ClimbZombieData = ClimbZombie->GetSettingData();
	if (false == ClimbZombieData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("ClimbZombieData Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	FVector Destination = GetValueAsVector(OwnerComp, TEXT("Destination"));

	FMotionWarpingTarget Target = {};
	Target.Name = FName("ClimbDestination");
	Target.Location = Destination;

	UMotionWarpingComponent* MotionWarpComp = ClimbZombie->GetMotionWarpingComponent();
	if (nullptr == MotionWarpComp)
	{
		LOG(MonsterLog, Fatal, TEXT("MotionWarpComp Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	MotionWarpComp->AddOrUpdateWarpTarget(Target);

	ClimbZombie->GetAIController()->StopMovement();
	ClimbZombie->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ClimbZombie->ChangeRandomAnimation(EBasicMonsterAnim::ClimbEnd);
	UMonsterRandomAnimInstance* AnimInst = ClimbZombie->GetAnimInstance();
	ClimbZombieData->TimeCount = AnimInst->GetKeyAnimMontage(EBasicMonsterAnim::ClimbEnd, ClimbZombie->GetAnimIndex())->GetPlayLength();
	
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_ClimbZombieClimbEnd::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AClimbZombie* ClimbZombie = GetSelfActor<AClimbZombie>(OwnerComp);
	UClimbZombieData* ClimbZombieData = ClimbZombie->GetSettingData();

	if (0.0f >= ClimbZombieData->TimeCount)
	{
		ClimbZombie->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
		ClimbZombie->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		StateChange(OwnerComp, EBasicMonsterState::Chase);
		return;
	}

	ClimbZombieData->TimeCount -= DeltaSeconds;
}
