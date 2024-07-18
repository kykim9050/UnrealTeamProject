// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Player/MainCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GenericTeamAgentInterface.h"


ABasicMonsterAIController::ABasicMonsterAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight_Config");

	UAIPerceptionComponent* AIPerception = CreateOptionalDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABasicMonsterAIController::PlayerDetect);
	AIPerception->SetDominantSense(*SightConfig->GetSenseImplementation());
	AIPerception->ConfigureSense(*SightConfig);

	SetPerceptionComponent(*AIPerception);
}

void ABasicMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTree);
}

void ABasicMonsterAIController::PlayerDetect(AActor* Other, FAIStimulus const Stimulus)
{
	if (false == Stimulus.WasSuccessfullySensed())
	{
		return;
	}

	AMainCharacter* TargetPlayer = Cast<AMainCharacter>(Other);
	if (nullptr == TargetPlayer)
	{
		return;
	}

	AMainPlayerState* TargetPlayerState = Cast<AMainPlayerState>(TargetPlayer->GetPlayerState());
	if (0.0f >= TargetPlayerState->GetPlayerHp())
	{
		return;
	}

	UObject* PrevTarget = GetBlackboardComponent()->GetValueAsObject("TargetActor");
	if (nullptr != PrevTarget)
	{
		return;
	}

	GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetPlayer);
}

ETeamAttitude::Type ABasicMonsterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	Super::GetTeamAttitudeTowards(Other);

	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (nullptr == OtherPawn)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (nullptr == OtherTeamAgent)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId MyTeamId = GetGenericTeamId();
	FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();
	if (MyTeamId == OtherTeamId)
	{
		return ETeamAttitude::Neutral;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}
}


