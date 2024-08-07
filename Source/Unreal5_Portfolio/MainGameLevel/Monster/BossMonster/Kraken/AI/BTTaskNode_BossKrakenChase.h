// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BTTaskNodeBase_Monster.h"
#include "BTTaskNode_BossKrakenChase.generated.h"

class ABossKraken;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BossKrakenChase : public UBTTaskNodeBase_Monster
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;

private:
	bool FindTarget(UBehaviorTreeComponent& OwnerComp);

private:
	const float TurnTime = 1.0f;
};
