// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/AI/BTTaskNode_BossHeartWalk.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

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

	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (false == MainGameInst->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MainGameInst Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	float RandomX = MainGameInst->Random.FRandRange(-1.0f, 1.0f);
	float RandomY = MainGameInst->Random.FRandRange(-1.0f, 1.0f);
	FVector Random2DVec = FVector(RandomX, RandomY, 0.0f);
	HeartData->WalkDir = Random2DVec.GetSafeNormal();
	
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
	if (0.0f >= HeartData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Idle);
		return;
	}

	Heart->AddMovementInput(HeartData->WalkDir, HeartData->BaseData->WalkSpeed);
	HeartData->TimeCount -= DeltaSeconds;
}
