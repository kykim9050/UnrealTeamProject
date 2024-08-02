// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicMonsterAIController.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABasicMonsterAIController();

private:
	UFUNCTION()
	void PlayerDetect(AActor* Other, FAIStimulus const Stimulus);

protected:
	void OnPossess(APawn* InPawn) override;
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree = nullptr;

private:
	// SenseConfig
	UPROPERTY()
	UAISenseConfig_Sight* SightConfig = nullptr;

};
