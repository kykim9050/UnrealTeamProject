// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Karaken/AI/MyBTTaskNode_KrakenIdle.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameState.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UMyBTTaskNode_KrakenIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ETestMonsterState CurState = static_cast<ETestMonsterState>(GetCurState(_OwnerComp));
	if (ETestMonsterState::Idle != CurState)
	{
		LOG(MonsterLog, Fatal, TEXT("Monster State Is Not Idle"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->IdleTime = 0.0f;
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Idle);

	return EBTNodeResult::Type::InProgress;
}

void UMyBTTaskNode_KrakenIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);

	AMainGameState* CurGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
	if (nullptr == CurGameState)
	{
		LOG(MonsterLog, Fatal, TEXT("CurGameState Is Null"));
		return;
	}

	if (3.0f < MonsterData->IdleTime)
	{
		UActorGroup* PlayerActorGroup = CurGameState->GetActorGroup(EObjectType::Player);
		if (nullptr == PlayerActorGroup)
		{
			return;
		}

		float MinDist = FLT_MAX;
		AActor* TargetPlayer = nullptr;
		for (AActor* Target : PlayerActorGroup->Actors)
		{
			FVector PlayerLocation = Target->GetActorLocation();
			PlayerLocation.Z = 0.0f;

			FVector MonsterLocation = Monster->GetActorLocation();
			MonsterLocation.Z = 0.0f;

			FVector MonsterToPlayer = MonsterLocation - PlayerLocation;

			float MonToPlayer = MonsterToPlayer.Size();
			if (MonToPlayer <= MinDist)
			{
				MinDist = MonToPlayer;
				TargetPlayer = Target;
			}
		}

		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetPlayer);
		StateChange(_OwnerComp, ETestMonsterState::Rotate);
		return;
	}

	MonsterData->IdleTime += _DeltaSeconds;
}