// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DrinkCompleteNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UDrinkCompleteNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
