// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodeBase_Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNodeBase_Monster::UBTTaskNodeBase_Monster()
{
	bNotifyTick = true;
}

uint8 UBTTaskNodeBase_Monster::GetCurState(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("CurState"));
}

void UBTTaskNodeBase_Monster::StateChange(UBehaviorTreeComponent& OwnerComp, uint8 NextState, EBTNodeResult::Type NodeResult)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurState"), NextState);
	FinishLatentTask(OwnerComp, NodeResult);
}

AActor* UBTTaskNodeBase_Monster::GetSelfActor(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
}

UObject* UBTTaskNodeBase_Monster::GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsObject(Name);
}

void UBTTaskNodeBase_Monster::SetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name, UObject* Value)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Name, Value);
}

FVector UBTTaskNodeBase_Monster::GetValueAsVector(UBehaviorTreeComponent& OwnerComp, FName Name)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsVector(Name);
}

void UBTTaskNodeBase_Monster::SetValueAsVector(UBehaviorTreeComponent& OwnerComp, FName Name, const FVector& Value)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Name, Value);
}
