// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMutantJumpAttack.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"
#include "MainGameLevel/Monster/BasicMonster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Monster/Animation/MonsterRandomAnimInstance.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MotionWarpingComponent.h"

#include "Global/ContentsLog.h"

#include "PartDevLevel/Character/ParentsCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

EBTNodeResult::Type UBTTaskNode_BasicMutantJumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMutant* Mutant = GetSelfActor<ABasicMutant>(OwnerComp);
	if (false == Mutant->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Mutant Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	UBasicMutantData* MutantData = Mutant->GetSettingData();
	if (false == Mutant->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("MutantData Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	ABasicMonsterAIController* AIController = Mutant->GetAIController();
	AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

	FMotionWarpingTarget Target = {};
	Target.Name = FName("JumpAttackTarget");
	Target.Location = TargetActor->GetActorLocation();
	Target.Rotation = TargetActor->GetActorRotation();

	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(Mutant->GetActorLocation(), Target.Location);
	Mutant->SetActorRotation(TurnRot);

	UMotionWarpingComponent* MotionWarpingComp = Mutant->GetMotionWarpingComponent();
	if (nullptr == MotionWarpingComp)
	{
		LOG(MonsterLog, Fatal, TEXT("MotionWarpingComp Is Not Valid"));
		return EBTNodeResult::Aborted;
	}

	MotionWarpingComp->AddOrUpdateWarpTarget(Target);

	Mutant->ChangeRandomAnimation(EBasicMonsterAnim::JumpAttack);
	UAnimMontage* JumpAttackMontage = Mutant->GetAnimInstance()->GetKeyAnimMontage(EBasicMonsterAnim::JumpAttack, Mutant->GetAnimIndex());
	MutantData->TimeCount = JumpAttackMontage->GetPlayLength();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMutantJumpAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMutant* Mutant = GetSelfActor<ABasicMutant>(OwnerComp);
	UBasicMutantData* MutantData = Mutant->GetSettingData();

	if (0.0f >= MutantData->TimeCount)
	{
		AParentsCharacter* TargetPlayer = GetValueAsObject<AParentsCharacter>(OwnerComp, TEXT("TargetActor"));
		ATestPlayerState* TargetPlayerState = Cast<ATestPlayerState>(TargetPlayer->GetPlayerState());

		if (0.0f >= TargetPlayerState->GetPlayerHp())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			StateChange(OwnerComp, EBasicMonsterState::Idle);
			return;
		}
		else
		{
			FVector MutantLocation = Mutant->GetActorLocation();
			FVector TargetLocation = TargetPlayer->GetActorLocation();

			FVector LocationDiff = TargetLocation - MutantLocation;
			float DiffLength = LocationDiff.Size();
			if (DiffLength <= MutantData->AttackRange)
			{
				StateChange(OwnerComp, EBasicMonsterState::Attack);
				return;
			}
			else if (DiffLength <= MutantData->JumpAttackMaxRange && DiffLength >= MutantData->JumpAttackMinRange)
			{
				StateChange(OwnerComp, EBasicMonsterState::JumpAttack);
				return;
			}
			else
			{
				StateChange(OwnerComp, EBasicMonsterState::Chase);
				return;
			}
		}
	}

	MutantData->TimeCount -= DeltaSeconds;
}
