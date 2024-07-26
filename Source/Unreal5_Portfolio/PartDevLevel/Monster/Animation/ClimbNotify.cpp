// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/ClimbNotify.h"

#include "MotionWarpingComponent.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

void UClimbNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr == Monster)
	{
		return;
	}

	UMotionWarpingComponent* MotionWarpComp = Monster->GetMotionWarpingComponent();
	if (nullptr == MotionWarpComp)
	{
		return;
	}

	AAIController* AIController = Cast< AAIController>(Monster->GetController());
	FVector Destination = AIController->GetBlackboardComponent()->GetValueAsVector(TEXT("DestinationLocation"));
	//Destination.Z += (Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 2.0f);

	FMotionWarpingTarget Target = {};
	Target.Name = FName("ClimbDest");
	Target.Location = Destination;
	//Target.Rotation = TargetActor->GetActorRotation();

	MotionWarpComp->AddOrUpdateWarpTarget(Target);
}
