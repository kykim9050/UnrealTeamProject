// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Karaken/AI/BTTaskNode_KrakenRotate.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsLog.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_KrakenRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	ETestMonsterState CurState = static_cast<ETestMonsterState>(GetCurState(OwnerComp));
	if (ETestMonsterState::Rotate != CurState)
	{
		LOG(MonsterLog, Fatal, TEXT("Monster State Is Not Rotate"));
		return EBTNodeResult::Type::Aborted;
	}

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	ETestMonsterAnim NextAnim;

	FVector MonsterLocation = Monster->GetActorLocation();
	MonsterLocation.Z = 0.0f;
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0.0f;

	FRotator Rotate = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
	double Rot = Rotate.Yaw;
	if (abs(Rot) <= 30.0f)
	{
		StateChange(OwnerComp, ETestMonsterState::Chase);
		return EBTNodeResult::Type::Succeeded;
	}
	else if (Rot > 30.0f)
	{
		NextAnim = ETestMonsterAnim::RRotate;
	}
	else if (Rot < -30.0f)
	{
		NextAnim = ETestMonsterAnim::LRotate;
	}

	MonsterData->DestRotate = Rotate;
	MonsterData->MyRotate = Monster->GetActorRotation();
	MonsterData->AnimationTime = 0.0f;
	Monster->ChangeRandomAnimation(NextAnim);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_KrakenRotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UMonsterData* MonsterData = GetValueAsObject<UMonsterData>(OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(OwnerComp);

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	FVector TargetLocation = Target->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector MonsterToTarget = MonsterLocation - TargetLocation;

	if (MonsterToTarget.Size() <= MonsterData->AttackBoundary)
	{
		FRotator Rotate = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, TargetLocation);
		double Rot = Rotate.Yaw;
		if (abs(Rot) <= 30.0f)
		{
			StateChange(OwnerComp, ETestMonsterState::Attack);
			return;
		}
	}
	
	float Alpha = FMath::Clamp(MonsterData->AnimationTime, 0.0f, 2.0f);
	FRotator TurnRotate = FMath::Lerp(MonsterData->MyRotate, MonsterData->DestRotate, Alpha * 0.5f);

	Monster->SetActorRotation(TurnRotate);

	if (2.0f < MonsterData->AnimationTime)
	{
		StateChange(OwnerComp, ETestMonsterState::Chase);
		return;
	}

	MonsterData->AnimationTime += DeltaSeconds;
}
