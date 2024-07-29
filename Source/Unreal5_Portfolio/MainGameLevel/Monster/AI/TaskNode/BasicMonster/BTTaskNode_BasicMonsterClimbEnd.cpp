// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/TaskNode/BasicMonster/BTTaskNode_BasicMonsterClimbEnd.h"
#include "MainGameLevel/Monster/Animation/BasicMonsterAnimInstance.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterClimbEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	MonsterData->ClimbTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::ClimbEnd, Monster->GetAnimIndex())->GetPlayLength();
	Monster->ChangeRandomAnimation(EBasicMonsterAnim::ClimbEnd);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMonsterClimbEnd::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));

	if (0.0f >= MonsterData->ClimbTime)
	{
		FVector Destination = GetValueAsVector(OwnerComp, TEXT("Destination"));
		FVector MonsterLocation = Monster->GetActorLocation();

		FVector DiffLocation = MonsterLocation - Destination;
		if (abs(DiffLocation.X) >= 50.0f || abs(DiffLocation.Y) >= 50.0f)
		{
			FVector DirVector = (Destination - MonsterLocation);
			DirVector.Normalize();
			Monster->SetActorLocation(MonsterLocation + DirVector * 50.0f);
		}
		else
		{
			Destination.Z += Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			Monster->GetCapsuleComponent()->SetCapsuleRadius(34.0f);
			Monster->SetActorRelativeLocation(Destination);
			Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
			StateChange(OwnerComp, ETestMonsterState::Chase);
			return;
		}
	}
	else
	{
		MonsterData->ClimbTime -= DeltaSeconds;
	}
}
