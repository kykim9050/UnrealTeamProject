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

	//Monster->ChangeAniValue(EMonsterAnim::ClimbEnd);
	Monster->ChangeAniValue(ETestMonsterAnim::ClimbEnd);
	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->ClimbTime = Monster->GetAnimInstance()->GetKeyAnimMontage(static_cast<uint8>(ETestMonsterAnim::ClimbEnd))->GetPlayLength();
	MonsterData->LerpPos = Monster->GetActorLocation();
	MonsterData->ClimbTotal = 0.0f;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Monster_ClimbEnd::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
	FVector DestLoc = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
	if (nullptr == Monster)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("Monster Is Null"));
		return;
	}
	Monster->AddMovementInput(Monster->GetActorForwardVector(), 20.0f);
	if (0.0f >= MonsterData->ClimbTime)
	{
		Monster->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
		StateChange(_OwnerComp, ETestMonsterState::Chase);
		return;
	}

	
	FVector LerpMove = FMath::Lerp(MonsterData->LerpPos, DestLoc, FMath::Clamp(MonsterData->ClimbTotal, 0.0f, 1.0f));
	Monster->SetActorLocation(LerpMove, false);
	MonsterData->ClimbTotal += _DeltaSeconds;
	MonsterData->ClimbTime -= _DeltaSeconds;
}
