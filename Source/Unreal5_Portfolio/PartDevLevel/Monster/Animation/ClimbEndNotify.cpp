// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/ClimbEndNotify.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"

void UClimbEndNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
}

void UClimbEndNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());

	if (nullptr != Monster)
	{
		//Monster->AddActorLocalOffset(FVector(0.0f, 0.0f, 5.0f) * FrameDeltaTime);
	}
}

void UClimbEndNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	//ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
	//FVector DestLoc = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
	//if (nullptr != Monster)
	//{
	//	Monster->SetActorLocation(DestLoc);
	//}
	
}
