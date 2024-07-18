// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/ClimbEndNotify.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"

void UClimbEndNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());

	if (nullptr != Monster)
	{
		FVector FirstPos = Monster->GetActorLocation();
		float ClimbDist = Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()/2.0f;
		ClimbVector = FirstPos;
		ClimbVector.Z += ClimbDist;
		ClimbVector.X = 0.0f;
		ClimbVector.Y = 0.0f;

		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		UMonsterData* MonsterData = Cast<UMonsterData>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("MonsterData")));
		AnimTime = MonsterData->ClimbTime;
	}
}

void UClimbEndNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());

	if (nullptr != Monster)
	{
		//ClimbVector.Z / AnimTime;
		Monster->AddActorLocalOffset(FVector(0.0f, 0.0f,(ClimbVector.Z / (AnimTime * 4.0f)) * FrameDeltaTime));
	}
}

void UClimbEndNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());

	if (nullptr != Monster)
	{
		Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
		Monster->ChangeAniValue(EMonsterAnim::Idle);
	}
}
