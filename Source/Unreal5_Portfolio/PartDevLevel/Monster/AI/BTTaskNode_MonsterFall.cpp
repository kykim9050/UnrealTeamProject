// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/AI/BTTaskNode_MonsterFall.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UBTTaskNode_MonsterFall::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("DestinationLocation"));
	FVector Velocity = FVector::ZeroVector;
	
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, MonsterLocation, LandingLocation, 0.0f, 0.5f);
	Monster->LaunchCharacter(Velocity, true, true);	

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_MonsterFall::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("DestinationLocation"));

	//MonsterLocation.Z = 0;
	//LandingLocation.Z = 0;
	
	FVector LocationDiff = MonsterLocation - LandingLocation;
	if (50.0f >= LocationDiff.Size())
	{
		StateChange(_OwnerComp, ETestMonsterState::Chase);
		return;
	}

	//FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, LandingLocation);
	//Monster->SetActorRotation(TurnRot);
}
