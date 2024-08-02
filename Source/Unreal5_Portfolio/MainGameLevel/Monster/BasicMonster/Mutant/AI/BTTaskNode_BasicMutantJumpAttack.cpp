// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMutantJumpAttack.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutant.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"
#include "MainGameLevel/Monster/Animation/MonsterRandomAnimInstance.h"

#include "Global/ContentsLog.h"

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

	Mutant->ChangeRandomAnimation(EBasicMonsterAnim::JumpAttack);
	UAnimMontage* JumpAttackMontage = Mutant->GetAnimInstance()->GetKeyAnimMontage(EBasicMonsterAnim::JumpAttack, Mutant->GetAnimIndex());
	MutantData->TimeCount = JumpAttackMontage->GetPlayLength();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_BasicMutantJumpAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

}
