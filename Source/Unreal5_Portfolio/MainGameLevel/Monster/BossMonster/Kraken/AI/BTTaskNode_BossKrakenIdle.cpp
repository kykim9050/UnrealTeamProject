// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/AI/BTTaskNode_BossKrakenIdle.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKraken.h"
#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenData.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Player/MainCharacter.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameState.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

EBTNodeResult::Type UBTTaskNode_BossKrakenIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	if (false == Kraken->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossKrakenData* KrakenData = Kraken->GetSettingData();
	KrakenData->TimeCount = IdleTime;
	Kraken->ChangeAnimation(EBossMonsterAnim::Idle);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossKrakenIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABossKraken* Kraken = GetSelfActor<ABossKraken>(OwnerComp);
	UBossMonsterData* KrakenData = Kraken->GetSettingData();

	if (0.0f >= KrakenData->TimeCount)
	{
		AMainGameState* CurGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
		UActorGroup* PlayerGroup = CurGameState->GetActorGroup(EObjectType::Player);
		if (nullptr == PlayerGroup)
		{
			LOG(MonsterLog, Fatal, TEXT("PlayerGroup Is Nullptr"));
			return;
		}

		float MinDist = FLT_MAX;
		AActor* TargetActor = nullptr;
		for (AActor* Actor : PlayerGroup->Actors)
		{
			// Player 상태 체크

			ATestCharacter* Player = Cast<ATestCharacter>(Actor);
			if (nullptr == Player)
			{
				LOG(MonsterLog, Fatal, TEXT("Player Is Nullptr"));
				return;
			}

			ATestPlayerState* TestPlayerState = Cast<ATestPlayerState>(Player->GetPlayerState());
			if (nullptr == TestPlayerState)
			{
				LOG(MonsterLog, Fatal, TEXT("TestPlayerState Is Nullptr"));
				return;
			}

			if (0.0f >= TestPlayerState->GetPlayerHp())
			{
				continue;
			}

			//AMainCharacter* Player = Cast<AMainCharacter>(Actor);
			//if (nullptr == Player)
			//{
			//	LOG(MonsterLog, Fatal, TEXT("Player Is Nullptr"));
			//	return;
			//}
			//
			//AMainPlayerState* MainPlayerState = Cast<AMainPlayerState>(Player->GetPlayerState());
			//if (nullptr == MainPlayerState)
			//{
			//	LOG(MonsterLog, Fatal, TEXT("MainPlayerState Is Nullptr"));
			//	return;
			//}
			//
			//if (0.0f >= MainPlayerState->GetPlayerHp())
			//{
			//	continue;
			//}

			// 최단 거리 Player 찾기
			FVector PlayerLocation = Player->GetActorLocation();
			PlayerLocation.Z = 0.0f;
			
			FVector MonsterLocation = Kraken->GetActorLocation();
			MonsterLocation.Z = 0.0f;

			FVector DiffLocation = MonsterLocation - PlayerLocation;

			float Diff = DiffLocation.Size();
			if (Diff <= MinDist)
			{
				MinDist = Diff;
				TargetActor = Player;
			}
		}

		if (nullptr != TargetActor)
		{
			SetValueAsObject(OwnerComp, TEXT("TargetActor"), TargetActor);
			StateChange(OwnerComp, EBossMonsterState::Chase);
			return;
		}
	}

	KrakenData->TimeCount -= DeltaSeconds;
}
