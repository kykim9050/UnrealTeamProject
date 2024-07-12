// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestBossMonsterAIControllerBase.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestBossMonsterAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	ATestBossMonsterAIControllerBase();
	void BeginPlay() override;

	UFUNCTION()
	void PlayerDetect(AActor* _Actor, FAIStimulus const _Stimulus);

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	void SetPerception();

private:
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Sight", meta = (AllowPrivateAccess = true))
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;
	
};
