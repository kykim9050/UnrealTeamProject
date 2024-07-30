// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MonsterJump.h"
#include "PartDevLevel/Monster/Base/TestMonsterBase.h"

#include "Kismet/GameplayStatics.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterJump::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("DestinationLocation"));
	LandingLocation.Z -= Monster->GetMesh()->GetRelativeLocation().Z;
	FVector Velocity = FVector::ZeroVector;

	UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, MonsterLocation, LandingLocation, 0.0f, 0.5f);
	Monster->LaunchCharacter(Velocity, true, true);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterJump::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("DestinationLocation"));

	MonsterLocation.Z = 0;
	LandingLocation.Z = 0;

	FVector LocationDiff = MonsterLocation - LandingLocation;
	if (50.0f >= LocationDiff.Size())
	{
		StateChange(_OwnerComp, ETestMonsterState::Chase);
		return;
	}
}
