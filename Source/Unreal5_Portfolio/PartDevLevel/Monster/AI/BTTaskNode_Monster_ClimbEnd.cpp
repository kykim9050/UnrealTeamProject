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

	Monster->ChangeAniValue(EMonsterAnim::ClimbEnd);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->ClimbTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(EMonsterAnim::ClimbEnd))->GetPlayLength();
	Monster->SetActorLocation(Monster->GetActorLocation() + Monster->GetActorForwardVector() * 10.0f);
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

	if(0.0f >= MonsterData->ClimbTime)
	{
		/*FVector LeftFootLoc = Monster->GetMesh()->GetBoneLocation("Base-HumanLLegDigit11", EBoneSpaces::WorldSpace);
		LeftFootLoc.Z += (Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
		Monster->SetActorLocation(LeftFootLoc);
		Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);*/
		StateChange(_OwnerComp, EMonsterState::Chase);
		return;
	}
	/*else
	{
		FVector FirstPos = Monster->GetActorLocation();
		float ClimbDist = Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 2.0f;
		FVector Result = FirstPos;
		Result.Z += ClimbDist;

		Monster->AddActorLocalOffset()
	}*/
}
