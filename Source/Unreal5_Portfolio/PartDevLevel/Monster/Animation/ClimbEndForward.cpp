// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/ClimbEndForward.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

void UClimbEndForward::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		if (nullptr != Controller)
		{
			UTestMonsterData* MonsterData = Cast<UTestMonsterData>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("MonsterData")));
			FVector ClimbDestLoc = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
			FVector CurLoc = Monster->GetActorLocation();
			MonsterData->LerpPos = CurLoc;
			MonsterData->DestLoc = ClimbDestLoc;
			MonsterData->DestLoc.Z = CurLoc.Z;
			MonsterData->ClimbEndUpTime = 0.6f;
		}
	}
}

void UClimbEndForward::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		if (nullptr != Controller)
		{
			UTestMonsterData* MonsterData = Cast<UTestMonsterData>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("MonsterData")));
			FVector LerpMove = FMath::Lerp(MonsterData->LerpPos, MonsterData->DestLoc, FMath::Clamp(MonsterData->ClimbEndUpTime, 0.0f, 1.0f));
			Monster->SetActorLocation(LerpMove, false);
			MonsterData->ClimbEndUpTime += FrameDeltaTime;
		}
	}
}

void UClimbEndForward::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		Monster->ChangeRandomAnimation(ETestMonsterAnim::Idle);
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		if (nullptr != Controller)
		{
			FVector DestLoc = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
			DestLoc.Z += Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			Monster->SetActorLocation(DestLoc);
			
		}
	}
}
