// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/AI/BTTaskNode_BasicMutantScream.h"

EBTNodeResult::Type UBTTaskNode_BasicMutantScream::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMutantScream::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);



}
