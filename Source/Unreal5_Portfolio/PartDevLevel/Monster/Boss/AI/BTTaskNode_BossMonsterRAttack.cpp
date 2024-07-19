// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonsterRAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/ContentsLog.h"
#include "Global/MainGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_BossMonsterRAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	if (false == BossMonster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));
	BossMonster->ChangeAniValue(EBossMonsterAnim::RangedAttack);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossMonsterRAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComp, TEXT("BossMonsterData"));

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComp);
	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));

	FVector MonsterLocation = BossMonster->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
	BossMonster->SetActorRotation(TurnRot);

	ATestCharacter* TargetPlayer = Cast<ATestCharacter>(TargetActor);
	ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(TargetPlayer->GetPlayerState());

	FVector LocationDiff = TargetLocation - MonsterLocation;
	float Dist = LocationDiff.Size();

	if (0.0f >= TargetPlayerState->GetPlayerHp())
	{
		StateChange(_OwnerComp, EBossMonsterState::Idle);
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		_OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), false);
		return;
	}
	else if (Dist <= BossData->Data->GetRangedAttackBoundary())
	{
		int RandomIndex = MainGameInst->Random.FRandRange(0, 10);

		if (5 > RandomIndex)
		{
			StateChange(_OwnerComp, EBossMonsterState::RangedAttack);
			return;
		}
		else
		{
			StateChange(_OwnerComp, EBossMonsterState::Chase);
			return;
		}
	}
	else if (Dist >= BossData->Data->GetRangedAttackBoundary())
	{
		StateChange(_OwnerComp, EBossMonsterState::Chase);
		return;
	}
}
