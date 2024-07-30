// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/ClimbEndNotify.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

void UClimbEndNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		if (nullptr != Controller)
		{
			UTestMonsterData* MonsterData = Cast<UTestMonsterData>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("MonsterData")));
			FVector ClimbDestLoc = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
			FVector CurLoc = MonsterData->LerpPos;
			CurLoc.Z = ClimbDestLoc.Z;
			MonsterData->DestLoc = CurLoc;
			MonsterData->ClimbEndUpTime = 2.3f;
		}
	}
}

void UClimbEndNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ATestMonsterBase* Monster = Cast<ATestMonsterBase>(MeshComp->GetOwner());
	if (nullptr != Monster)
	{
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		if (nullptr != Controller)
		{
			/*UMonsterData* MonsterData = Cast<UMonsterData>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("MonsterData")));
			FVector LerpMove = FMath::Lerp(MonsterData->LerpPos, MonsterData->DestLoc, FMath::Clamp(MonsterData->ClimbEndUpTime, 0.0f, 1.0f));
			Monster->SetActorLocation(LerpMove, false);
			MonsterData->ClimbEndUpTime += FrameDeltaTime;*/
		}
	}
}

void UClimbEndNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
