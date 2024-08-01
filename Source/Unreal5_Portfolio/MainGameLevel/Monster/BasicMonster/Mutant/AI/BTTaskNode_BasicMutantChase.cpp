// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMutantChase.h"

EBTNodeResult::Type UBTTaskNode_BasicMutantChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMutantChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);



}
