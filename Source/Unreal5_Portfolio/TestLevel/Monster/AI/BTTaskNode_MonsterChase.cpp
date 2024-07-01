// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterChase.h"

#include "TestLevel/Monster/TestMonsterBaseAIController.h"
#include "TestLevel/Monster/TestMonsterBase.h"

#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_MonsterChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> Monster Is Not Valid"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterData->Data->GetRunSpeed();
	Monster->ChangeAnimation(EMonsterAnim::Run);
	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);

	UObject* TargetObject = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);
	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(TargetActor->GetActorLocation());

	// 범위 안에 있으면 공격상태로 변경
}
