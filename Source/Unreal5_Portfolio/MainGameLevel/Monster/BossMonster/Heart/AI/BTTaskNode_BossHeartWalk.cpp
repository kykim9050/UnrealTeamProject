// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/AI/BTTaskNode_BossHeartWalk.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

#include "PartDevLevel/Character/ParentsCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

EBTNodeResult::Type UBTTaskNode_BossHeartWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	if (false == Heart->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Heart Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossHeartData* HeartData = Heart->GetSettingData();
	if (false == HeartData->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("HeartData Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}
	
	FNavLocation PatrolLocation(FVector::ZeroVector);
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	bool IsFind = NavSystem->GetRandomReachablePointInRadius(HeartData->WalkOriginPos, HeartData->WalkRaidus, PatrolLocation);
	if (false == IsFind)
	{
		return EBTNodeResult::Type::Failed;
	}

	SetValueAsVector(OwnerComp, TEXT("Destination"), PatrolLocation.Location);

	Heart->GetCharacterMovement()->MaxWalkSpeed = HeartData->BaseData->WalkSpeed;
	Heart->ChangeAnimation(EBossMonsterAnim::WalK);
	HeartData->TimeCount = WalkTime;

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossHeartWalk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	UBossHeartData* HeartData = Heart->GetSettingData();

	FVector WalkLocation = GetValueAsVector(OwnerComp, TEXT("Destination"));
	EPathFollowingRequestResult::Type IsMove = Heart->GetAIController()->MoveToLocation(WalkLocation);

	if (0.0f >= HeartData->TimeCount || EPathFollowingRequestResult::Type::AlreadyAtGoal == IsMove)
	{
		// ·£´ý Å¸°Ù Ã£±â
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		bool bFindTarget = FindRandomTarget(OwnerComp, MainGameInst);
		if (true == bFindTarget)
		{
			int32 NextState = MainGameInst->Random.RandRange(0, 1);
			switch (NextState)
			{
			case 0:
				StateChange(OwnerComp, EBossMonsterState::Chase);
				return;
			case 1:
				StateChange(OwnerComp, EBossMonsterState::RangedAttack);
				return;
			}
		}

		StateChange(OwnerComp, EBossMonsterState::Idle);
		return;
	}


	HeartData->TimeCount -= DeltaSeconds;
}

bool UBTTaskNode_BossHeartWalk::FindRandomTarget(UBehaviorTreeComponent& OwnerComp, UMainGameInstance* MainGameInst)
{
	AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
	if (false == MainGameState->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MainGameState Is Not Valid"));
		return false;
	}

	UActorGroup* PlayerGroup = MainGameState->GetActorGroup(EObjectType::Player);

	bool AllDeadCheck = true;
	for (AActor* CurActor : PlayerGroup->Actors)
	{
		AParentsCharacter* CurPlayer = Cast<AParentsCharacter>(CurActor);
		if (false == CurPlayer->IsValidLowLevel())
		{
			LOG(MonsterLog, Fatal, TEXT("CurPlayer Is Not Valid"));
			return false;
		}
		
		ATestPlayerState* CurPlayerState = CurPlayer->GetPlayerState<ATestPlayerState>();
		if (false == CurPlayerState->IsValidLowLevel())
		{
			LOG(MonsterLog, Fatal, TEXT("CurPlayerState Is Not Valid"));
			return false;
		}

		if (0.0f < CurPlayerState->GetPlayerHp())
		{
			AllDeadCheck = false;
			break;
		}
	}

	if (false == AllDeadCheck)
	{
		AActor* TargetActor = nullptr;
		while (nullptr == TargetActor)
		{
			int32 PlayerIndex = MainGameInst->Random.RandRange(0, PlayerGroup->Actors.Num() - 1);
			
			AParentsCharacter* CurPlayer = Cast<AParentsCharacter>(PlayerGroup->Actors[PlayerIndex]);
			ATestPlayerState* CurPlayerState = CurPlayer->GetPlayerState<ATestPlayerState>();
			if (0.0f < CurPlayerState->GetPlayerHp())
			{
				TargetActor = CurPlayer;
				break;
			}
		}

		SetValueAsObject(OwnerComp, TEXT("TargetActor"), TargetActor);
		return true;
	}
	else
	{
		SetValueAsObject(OwnerComp, TEXT("TargetActor"), nullptr);
		return false;
	}
}
