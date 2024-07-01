// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterBaseAIController.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GenericTeamAgentInterface.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsEnum.h"

ATestMonsterBaseAIController::ATestMonsterBaseAIController()
{
	SetPerception();
	SetGenericTeamId(FGenericTeamId(2));
}

void ATestMonsterBaseAIController::BeginPlay()
{
	Super::BeginPlay();


}

void ATestMonsterBaseAIController::PlayerDetect(AActor* Actor, FAIStimulus const Stimulus)
{
	if (nullptr != Actor)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), Stimulus.WasSuccessfullySensed());
		if (true == GetBlackboardComponent()->GetValueAsBool(TEXT("CanSeePlayer")))
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
		}
	}
}

ETeamAttitude::Type ATestMonsterBaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	Super::GetTeamAttitudeTowards(Other);
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (nullptr != OtherPawn)
	{
		const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
		if (nullptr != OtherTeamAgent)
		{
			FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();
			if (GetGenericTeamId() == OtherTeamId)
			{
				return ETeamAttitude::Neutral;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

void ATestMonsterBaseAIController::SetPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Confing"));

	UAIPerceptionComponent* AIPerception = CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SetPerceptionComponent(*AIPerception);

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATestMonsterBaseAIController::PlayerDetect);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
