// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "StageCheckBox.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AStageCheckBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AStageCheckBox();

protected:

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(Reliable, NetMulticast)
	void DestroyTrigger();
	void DestroyTrigger_Implementation();

private:

};
