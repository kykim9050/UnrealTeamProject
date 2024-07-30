// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/TriggerBox/StageCheckBox.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

AStageCheckBox::AStageCheckBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AStageCheckBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AStageCheckBox::OnOverlapEnd);
}


void AStageCheckBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	int a = 0;
}

void AStageCheckBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	int a = 0;
}