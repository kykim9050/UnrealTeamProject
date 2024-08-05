// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/Notify/BasicMutantJumpAttackNotify.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MotionWarpingComponent.h"
#include "AIController.h"

void UBasicMutantJumpAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ABasicMutant* Mutant = Cast<ABasicMutant>(MeshComp->GetOwner());
	if (nullptr == Mutant)
	{
		return;
	}

	ABasicMonsterAIController* AIController = Mutant->GetAIController();	
	if (nullptr == AIController)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

	FMotionWarpingTarget Target = {};
	Target.Name = FName("JumpAttackTarget");
	Target.Location = TargetActor->GetActorLocation();

	UMotionWarpingComponent* MotionWarpingComp = Mutant->GetMotionWarpingComponent();
	if (nullptr == MotionWarpingComp)
	{
		return;
	}

	MotionWarpingComp->AddOrUpdateWarpTarget(Target);
}
