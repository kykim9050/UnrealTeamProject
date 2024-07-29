// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/TaskNode/BTTaskNodeBase_BasicMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNodeBase_BasicMonster::UBTTaskNodeBase_BasicMonster()
{
	bNotifyTick = true;
}

uint8 UBTTaskNodeBase_BasicMonster::GetCurState(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("State"));
}

void UBTTaskNodeBase_BasicMonster::StateChange(UBehaviorTreeComponent& OwnerComp, uint8 NextState, EBTNodeResult::Type NodeResult)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), NextState);
	FinishLatentTask(OwnerComp, NodeResult);
}

AActor* UBTTaskNodeBase_BasicMonster::GetSelfActor(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
}

UObject* UBTTaskNodeBase_BasicMonster::GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsObject(Name);
}

void UBTTaskNodeBase_BasicMonster::SetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name, UObject* Value)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Name, Value);
}

FVector UBTTaskNodeBase_BasicMonster::GetValueAsVector(UBehaviorTreeComponent& OwnerComp, FName Name)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsVector(Name);
}

void UBTTaskNodeBase_BasicMonster::SetValueAsVector(UBehaviorTreeComponent& OwnerComp, FName Name, const FVector& Value)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Name, Value);
}
