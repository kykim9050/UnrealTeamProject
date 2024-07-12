// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonster.h"
#include "Global/ContentsEnum.h"

UBTTaskNode_BossMonster::UBTTaskNode_BossMonster()
{
	bNotifyTick = true;
}

AActor* UBTTaskNode_BossMonster::GetActor(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Object = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	return Cast<AActor>(Object);
}

uint8 UBTTaskNode_BossMonster::GetCurState(UBehaviorTreeComponent& _OwnerComp)
{
	return _OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("State"));
}

void UBTTaskNode_BossMonster::StateChange(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange)
{
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}