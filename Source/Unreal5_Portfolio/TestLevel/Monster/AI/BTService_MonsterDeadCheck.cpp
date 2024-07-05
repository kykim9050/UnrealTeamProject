// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTService_MonsterDeadCheck.h"
#include "TestLevel/Monster/TestMonsterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/ContentsEnum.h"

UBTService_MonsterDeadCheck::UBTService_MonsterDeadCheck()
{
	bNotifyBecomeRelevant = true;

	Interval = 0.0f;
	RandomDeviation = 0.0f;
}

void UBTService_MonsterDeadCheck::TickNode(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory, float _DeltaSeconds)
{
	Super::TickNode(_OwnerComp, _NodeMemory, _DeltaSeconds);

	UBlackboardComponent* BlackBoard = _OwnerComp.GetBlackboardComponent();

	UObject* Object = BlackBoard->GetValueAsObject(TEXT("SelfActor"));
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(Object);

	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> Monster Is Not Valid"), __FUNCTION__, __LINE__);
	}

	if (0.0f >= Monster->GetMonsterHp())
	{
		BlackBoard->SetValueAsEnum(TEXT("State"), static_cast<uint8>(EMonsterState::Dead));
	}
}
