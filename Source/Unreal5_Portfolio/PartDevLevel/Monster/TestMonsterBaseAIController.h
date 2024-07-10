// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestMonsterBaseAIController.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestMonsterBaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATestMonsterBaseAIController();
	void BeginPlay() override;

	UFUNCTION()
	void PlayerDetect(AActor* Actor, FAIStimulus const Stimulus);

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	

protected:
	void SetPerception();

private:
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Sight", meta = (AllowPrivateAccess = true))
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;
};
