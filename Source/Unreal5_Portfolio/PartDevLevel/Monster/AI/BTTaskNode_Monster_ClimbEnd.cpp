// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_Monster_ClimbEnd.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "Global/ContentsLog.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationData.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_Monster_ClimbEnd::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	Monster->ChangeRandomAnimation(ETestMonsterAnim::ClimbEnd);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->ClimbTime = Monster->GetAnimInstance()->GetKeyAnimMontage(ETestMonsterAnim::ClimbEnd, 0)->GetPlayLength();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Monster_ClimbEnd::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}

		/*FVector DirVector = (Dest - CurPos);
		DirVector.Normalize();
		if (abs(CurPos.X - Dest.X) >= 50.0f || abs(CurPos.Y - Dest.Y) >= 50.0f)
		{
			Monster->SetActorLocation(CurPos + DirVector * 50.0f);
		}
		else
		{*/
			/*Dest.Z += Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			Monster->GetCapsuleComponent()->SetCapsuleRadius(34.0f);
			Monster->SetActorRelativeLocation(Dest);*/
			Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
			StateChange(_OwnerComp, ETestMonsterState::Chase);
			return;
		//}
	//}
	/*else
	{
		FVector FirstPos = Monster->GetActorLocation();
		float ClimbDist = Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 2.0f;
		FVector Result = FirstPos;
		Result.Z += ClimbDist;

		Monster->AddActorLocalOffset()
	}*/
}
