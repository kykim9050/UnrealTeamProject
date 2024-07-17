// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/AI/BasicMonsterAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


ABasicMonsterAIController::ABasicMonsterAIController()
{
}

void ABasicMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree()
}
