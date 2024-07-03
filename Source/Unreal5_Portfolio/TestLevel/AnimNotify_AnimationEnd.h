// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AnimNotify_AnimationEnd.generated.h"

class ATestMonsterBase;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UAnimNotify_AnimationEnd : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_AnimationEnd();

public:
	ATestMonsterBase* Monster;

private:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
