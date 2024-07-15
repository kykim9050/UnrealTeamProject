// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterClimb.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "Components/CapsuleComponent.h"

EBTNodeResult::Type UBTTaskNode_MonsterClimb::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	//Monster->GetCharacterMovement()->GravityScale = 0.0f;
	Monster->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
	Monster->GetCharacterMovement()->MaxFlySpeed = 200.0f;
	Monster->ChangeAniValue(EMonsterAnim::Climb);
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MonsterClimb::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
	FVector Dest = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
	FVector CurPos = Monster->GetActorLocation();
	FVector ForwardVector = Monster->GetActorForwardVector();
	
	if (CurPos.Z >= Dest.Z - Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())
	{
		Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		StateChange(_OwnerComp, EMonsterState::ClimbEnd);
		return;
	}
}
