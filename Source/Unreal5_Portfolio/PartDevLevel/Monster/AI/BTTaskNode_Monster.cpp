// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_Monster.h"
#include "Global/ContentsEnum.h"

UBTTaskNode_Monster::UBTTaskNode_Monster()
{
	bNotifyTick = true;
}

AActor* UBTTaskNode_Monster::GetActor(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Object = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	return Cast<AActor>(Object);
}

uint8 UBTTaskNode_Monster::GetCurState(UBehaviorTreeComponent& _OwnerComp)
{
	return _OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("State"));
}

void UBTTaskNode_Monster::StateChange(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange, EBTNodeResult::Type _EBTNodeResult)
{
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), _StateChange);
	FinishLatentTask(_OwnerComp, _EBTNodeResult);
}