// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/MyBTTaskNode_MonsterClimb.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UMyBTTaskNode_MonsterClimb::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->SetClimbCollision(true);
	return EBTNodeResult::InProgress;
}

void UMyBTTaskNode_MonsterClimb::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector UpVector = Monster->GetActorUpVector();
	FVector ForwardVector = Monster->GetActorForwardVector();
	FVector CurPos = Monster->GetActorLocation();
	float WalkSpeed = Monster->GetMovementComponent()->GetMaxSpeed();
	Monster->GetMovementComponent()->SetActive(false);
	Monster->SetActorLocation(CurPos + UpVector * 50.0f * _DeltaSeconds, true);
}
