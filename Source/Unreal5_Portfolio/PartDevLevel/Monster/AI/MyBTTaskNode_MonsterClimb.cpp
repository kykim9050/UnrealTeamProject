// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/MyBTTaskNode_MonsterClimb.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"

EBTNodeResult::Type UMyBTTaskNode_MonsterClimb::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Monster->GetMovementComponent()->SetActive(false);
	return EBTNodeResult::InProgress;
}

void UMyBTTaskNode_MonsterClimb::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
	FVector Dest = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
	FVector CurPos = Monster->GetActorLocation();
	FVector UpVector = Monster->GetActorUpVector();
	if (CurPos.Z < Dest.Z)
	{
		FTransform AddTransform;
		AddTransform.SetLocation(UpVector * 500.0f * _DeltaSeconds);
		Monster->AddActorWorldTransform(AddTransform);
	}
	else
	{
		StateChange(_OwnerComp, EMonsterState::Chase);
		return;
	}
}
