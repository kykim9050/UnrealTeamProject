// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/AI/BTTaskNode_BossKrakenChase.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossKrakenChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	if (false == Kraken->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Kraken Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossKrakenData* KrakenData = Kraken->GetSettingData();
	if (false == KrakenData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("KrakenData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	Kraken->GetCharacterMovement()->MaxWalkSpeed = KrakenData->BaseData->ChaseSpeed;
	Kraken->ChangeAnimation(EBossMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossKrakenChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	
	AActor* Target = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	
	EPathFollowingRequestResult::Type IsMove = Kraken->GetAIController()->MoveToLocation(Target->GetActorLocation());

	//FVector LocationDiff = Target->GetActorLocation() - Monster->GetActorLocation();
	//double DiffLength = LocationDiff.Size();
	//if (DiffLength <= MonsterData->AttackRange)
	//{
	//	StateChange(OwnerComp, ETestMonsterState::Attack);
	//	return;
	//}
	//
	//if (IsMove == EPathFollowingRequestResult::Type::AlreadyAtGoal)
	//{
	//	MonsterData->IsGroundAttack = true;
	//	StateChange(OwnerComp, ETestMonsterState::Rotate);
	//	return;
	//}
}
