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

    return EBTNodeResult::Type();
}

void UBTTaskNode_BossMonsterRAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
