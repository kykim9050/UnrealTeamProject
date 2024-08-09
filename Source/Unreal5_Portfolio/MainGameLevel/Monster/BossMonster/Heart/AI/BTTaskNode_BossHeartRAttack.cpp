// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/AI/BTTaskNode_BossHeartRAttack.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartData.h"
#include "MainGameLevel/Monster/BossMonster/Heart/BossHeart.h"

#include "Kismet/KismetMathLibrary.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BossHeartRAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Heart->ChangeAnimation(EBossMonsterAnim::RangedAttack);
	UAnimMontage* MeleeAttackMontage = Heart->GetAnimInstance()->GetKeyAnimMontage(EBossMonsterAnim::RangedAttack);
	HeartData->AttackDamage = HeartData->BaseData->MeleeAttackDamage;
	HeartData->TimeCount = MeleeAttackMontage->GetPlayLength();
	Heart->GetAIController()->StopMovement();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossHeartRAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABossHeart* Heart = GetSelfActor<ABossHeart>(OwnerComp);
	FVector HeartLocation = Heart->GetActorLocation();
	HeartLocation.Z = 0.0f;
	
	AActor* TargetActor = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();
	TargetLocation.Z = 0.0f;

	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(HeartLocation, TargetLocation);
	Heart->SetActorRotation(TurnRot);

	UBossHeartData* HeartData = Heart->GetSettingData();
	if (0.0f >= HeartData->TimeCount)
	{
		StateChange(OwnerComp, EBossMonsterState::Idle);
		return;
	}

	HeartData->TimeCount -= DeltaSeconds;
}
