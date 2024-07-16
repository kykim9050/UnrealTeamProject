// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonsterChase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterAIControllerBase.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

#include "TestLevel/Character/TestCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossMonsterChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	if (false == BossMonster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> BossMonster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));
	BossMonster->GetCharacterMovement()->MaxWalkSpeed = BossData->Data->GetRunSpeed();
	BossMonster->ChangeAniValue(EBossMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossMonsterChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (EBossMonsterState::Chase != static_cast<EBossMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));
	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	FVector MonsterLocation = BossMonster->GetActorLocation();

    // 모든 플레이어 위치 가져오기
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestCharacter::StaticClass(), Players);

    AActor* ClosestPlayer = nullptr;
    float ClosestDistanceSq = MAX_FLT;

    // 가장 가까운 플레이어 찾기
    for (AActor* Player : Players)
    {
        FVector PlayerLocation = Player->GetActorLocation();
        float DistanceSq = FVector::DistSquared(PlayerLocation, MonsterLocation);

        if (DistanceSq < ClosestDistanceSq)
        {
            ClosestDistanceSq = DistanceSq;
            ClosestPlayer = Player;
        }
    }

    if (ClosestPlayer)
    {
        // 가장 가까운 플레이어의 위치로 이동 요청
        FVector TargetLocation = ClosestPlayer->GetActorLocation();
        EPathFollowingRequestResult::Type IsMove = BossMonster->GetBossAIController()->MoveToLocation(TargetLocation);

        // 공격 범위 내에 있다면 공격 상태로 변경
        //if (FVector::Dist(TargetLocation, MonsterLocation) <= BossData->Data->GetMeleeAttackBoundary())
        //{
        //    StateChange(_OwnerComp, EBossMonsterState::MeleeAttack);
        //    return;
        //}
    }
}