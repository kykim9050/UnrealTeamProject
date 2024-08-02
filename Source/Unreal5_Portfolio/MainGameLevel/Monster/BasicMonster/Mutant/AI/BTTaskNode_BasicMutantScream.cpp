// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BasicMonster/Mutant/AI/BTTaskNode_BasicMutantScream.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"
#include "MainGameLevel/Monster/Animation/MonsterRandomAnimInstance.h"

#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMutantScream::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Mutant->ChangeRandomAnimation(EBasicMonsterAnim::Scream);
	MutantData->TimeCount = Mutant->GetAnimInstance()->GetKeyAnimMontage(EBasicMonsterAnim::Scream, Mutant->GetAnimIndex())->GetPlayLength();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMutantScream::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMutant* Mutant = GetSelfActor<ABasicMutant>(OwnerComp);
	UBasicMutantData* MutantData = Mutant->GetSettingData();

	FVector MutantPos = Mutant->GetActorLocation();
	FVector TargetPos = GetValueAsObject<AActor>(OwnerComp, TEXT("TargetActor"))->GetActorLocation();
	
	MutantPos.Z = 0.0f;
	TargetPos.Z = 0.0f;
	
	FRotator NextRot = UKismetMathLibrary::FindLookAtRotation(MutantPos, TargetPos);
	Mutant->SetActorRotation(NextRot);

	// Scream Animation End
	if (0.0f >= MutantData->TimeCount)
	{
		StateChange(OwnerComp, EBasicMonsterState::Chase);
		return;
	}

	MutantData->TimeCount -= DeltaSeconds;
}
