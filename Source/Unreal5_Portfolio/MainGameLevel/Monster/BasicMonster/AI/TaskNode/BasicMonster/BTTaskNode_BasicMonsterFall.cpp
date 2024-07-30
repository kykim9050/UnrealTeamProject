// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_BasicMonsterFall.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_BasicMonsterFall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(OwnerComp, TEXT("Destination"));
	FVector Velocity = FVector::ZeroVector;

	UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, MonsterLocation, LandingLocation, 0.0f, 0.5f);
	Monster->LaunchCharacter(Velocity, true, true);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_BasicMonsterFall::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	ABasicMonsterBase* Monster = GetSelfActor<ABasicMonsterBase>(OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(OwnerComp, TEXT("Destination"));

	MonsterLocation.Z = 0;
	LandingLocation.Z = 0;

	FVector LocationDiff = MonsterLocation - LandingLocation;
	float Distance = LocationDiff.Size();
	if (50.0f >= Distance)
	{
		StateChange(OwnerComp, EBasicMonsterState::Chase);
		return;
	}
}
