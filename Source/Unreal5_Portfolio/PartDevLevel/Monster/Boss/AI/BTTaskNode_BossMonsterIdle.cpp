// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonsterIdle.h"
#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"
#include "Global/DataTable/BossDataRow.h"
#include "Global/ContentsLog.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_BossMonsterIdle::ExecuteTask(UBehaviorTreeComponent& _OwnerComponent, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComponent, _NodeMemory);

	ATestBossMonsterBase* BossMonster = GetActor<ATestBossMonsterBase>(_OwnerComponent);
	if (false == BossMonster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("BossMonster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComponent, TEXT("BossData"));
	
	BossMonster->ChangeAniValue(EBossMonsterAnim::Idle);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BossMonsterIdle::TickTask(UBehaviorTreeComponent& _OwnerComponent, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComponent, _pNodeMemory, _DeltaSeconds);

	UBossData* BossData = GetValueAsObject<UBossData>(_OwnerComponent, TEXT("BossData"));

	AMainGameState* GameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
	UActorGroup* Players = GameState->GetActorGroup(EObjectType::Player);


}
