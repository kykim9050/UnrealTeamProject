// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_KrakenAttack.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_KrakenAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ETestMonsterState CurState = static_cast<ETestMonsterState>(GetCurState(OwnerComp));
	if (ETestMonsterState::Attack != CurState)
	{
		LOG(MonsterLog, Fatal, TEXT("Monster State Is Not Attack"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(OwnerComp, TEXT("MonsterData"));
	AActor* Target = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"));
	ETestMonsterAnim NextAnim;

	FVector MonsterLocation = Monster->GetActorLocation();
	MonsterLocation.Z = 0.0f;
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0.0f;

	FRotator Rotate = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
	double Rot = Rotate.Yaw;
	if (abs(Rot) <= 45.0f)
	{
		NextAnim = ETestMonsterAnim::Attack;
	}
	else if (Rot > 45.0f)
	{
		NextAnim = ETestMonsterAnim::RAttack;
	}
	else if (Rot < -45.0f)
	{
		NextAnim = ETestMonsterAnim::LAttack;
	}

	Monster->ChangeRandomAnimation(NextAnim);
	Monster->SetActorRotation(Rotate);
	MonsterData->AnimationTime = Monster->GetAnimInstance()->GetKeyAnimMontage(NextAnim, Monster->GetAniIndex())->GetPlayLength();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_KrakenAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);


	UTestMonsterDataBase* MonsterData = GetValueAsObject<UTestMonsterDataBase>(OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);

	if (0.0f >= MonsterData->AnimationTime)
	{
		StateChange(OwnerComp, ETestMonsterState::Idle);
		return;
	}

	MonsterData->AnimationTime -= DeltaSeconds;
}
