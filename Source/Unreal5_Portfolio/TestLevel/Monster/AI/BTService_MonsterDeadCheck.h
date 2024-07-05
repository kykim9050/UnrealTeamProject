// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MonsterDeadCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTService_MonsterDeadCheck : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_MonsterDeadCheck();

	void TickNode(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory, float _DeltaSeconds) override;
	
};
