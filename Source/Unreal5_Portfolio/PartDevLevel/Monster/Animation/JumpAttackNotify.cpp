// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/JumpAttackNotify.h"

#include "MotionWarpingComponent.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UJumpAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr == Monster)
	{
		return;
	}

	if (false == Monster->HasAuthority())
	{
		return;
	}


	UMotionWarpingComponent* MotionWarpComp = Monster->GetMotionWarpingComponent();
	if (nullptr == MotionWarpComp)
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(Monster->GetController());
	AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

	FMotionWarpingTarget Target = {};
	Target.Name = FName("Target");
	Target.Location = TargetActor->GetActorLocation();
	Target.Rotation = TargetActor->GetActorRotation();

	MotionWarpComp->AddOrUpdateWarpTarget(Target);
}
