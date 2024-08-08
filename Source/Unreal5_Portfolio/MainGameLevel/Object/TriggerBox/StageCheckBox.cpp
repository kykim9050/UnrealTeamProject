// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/TriggerBox/StageCheckBox.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Global/MainGameState.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"

AStageCheckBox::AStageCheckBox()
{
	bReplicates = true;

	OnActorBeginOverlap.AddDynamic(this, &AStageCheckBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AStageCheckBox::OnOverlapEnd);
}


void AStageCheckBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (false == HasAuthority())
	{
		return;
	}

	AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

	if (nullptr == MainGameState)
	{
		LOG(ObjectLog, Fatal, "if (nullptr == MainGameState)");
		return;
	}

	MainGameState->AddPlayerCount();

	MainGameState->GameStateCheck(OtherActor);

	if (true == MainGameState->GetIsStageChange())
	{
		MainGameState->SetIsStageChange(false);
		DestroyTrigger();
	}
}

void AStageCheckBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (false == HasAuthority())
	{
		return;
	}

	AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

	if (nullptr == MainGameState)
	{
		LOG(ObjectLog, Fatal, "if (nullptr == MainGameState)");
		return;
	}

	MainGameState->SubPlayerCount();
}

void AStageCheckBox::DestroyTrigger_Implementation()
{
	Destroy();
}