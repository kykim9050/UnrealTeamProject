// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BTTaskNodeBase_Monster.h"
#include "BTTaskNode_BossHeartWalk.generated.h"

class UMainGameInstance;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BossHeartWalk : public UBTTaskNodeBase_Monster
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;

private:
	bool FindRandomTarget(UBehaviorTreeComponent& OwnerComp, UMainGameInstance* MainGameInst);

private:
	const float WalkTime = 2.5f;
	
};
