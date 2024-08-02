// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "KrakenAttackNotify.generated.h"

/**
 * 
 */
// 크라켄 파티클 소환 타이밍
UCLASS()
class UNREAL5_PORTFOLIO_API UKrakenAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
