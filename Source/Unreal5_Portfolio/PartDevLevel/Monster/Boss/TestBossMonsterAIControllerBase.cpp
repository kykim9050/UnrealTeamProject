// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/TestBossMonsterAIControllerBase.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GenericTeamAgentInterface.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsEnum.h"

ATestBossMonsterAIControllerBase::ATestBossMonsterAIControllerBase()
{
	SetPerception();
	SetGenericTeamId(FGenericTeamId(2));
}

void ATestBossMonsterAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}

void ATestBossMonsterAIControllerBase::PlayerDetect(AActor* _Actor, FAIStimulus const _Stimulus)
{
	ATestCharacter* Player = Cast<ATestCharacter>(_Actor);
	if (nullptr == Player)
	{
		return;
	}

	ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(Player->GetPlayerState());
	if (0 < TargetPlayerState->GetPlayerHp())
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), _Stimulus.WasSuccessfullySensed());
		if (true == GetBlackboardComponent()->GetValueAsBool(TEXT("CanSeePlayer")))
		{
			UObject* PrevObject = GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"));
			if (nullptr == PrevObject)
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), _Actor);
			}
		}
	}
}

ETeamAttitude::Type ATestBossMonsterAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
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

void ATestBossMonsterAIControllerBase::SetPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Confing"));

	UAIPerceptionComponent* AIPerception = CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SetPerceptionComponent(*AIPerception);

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATestBossMonsterAIControllerBase::PlayerDetect);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
