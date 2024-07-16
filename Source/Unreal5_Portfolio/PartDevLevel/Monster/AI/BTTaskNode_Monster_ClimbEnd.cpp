// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_Monster_ClimbEnd.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "Global/ContentsLog.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationData.h"

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

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Monster_ClimbEnd::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if(0.0f >= MonsterData->ClimbTime)
	{
		ATestMonsterBaseAIController* Controller = Cast<ATestMonsterBaseAIController>(Monster->GetController());
		FVector Dest = Controller->GetBlackboardComponent()->GetValueAsVector("DestinationLocation");
		Dest.Z = 0.0f;
		FVector CurPos = Monster->GetActorLocation();
		CurPos.Z = 0.0f;
		
	}
	MonsterData->ClimbTime -= _DeltaSeconds;


}
