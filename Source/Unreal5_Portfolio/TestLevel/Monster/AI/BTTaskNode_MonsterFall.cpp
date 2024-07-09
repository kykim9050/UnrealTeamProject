// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/AI/BTTaskNode_MonsterFall.h"
#include "TestLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_MonsterFall::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> Monster Is Not Valid"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Type::Aborted;
	}

	FVector MonsterLocation = Monster->GetActorLocation();
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("LandingLocation"));
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
	FVector LandingLocation = GetValueAsVector(_OwnerComp, TEXT("LandingLocation"));

	MonsterLocation.Z = 0;
	LandingLocation.Z = 0;
	
	FVector LocationDiff = MonsterLocation - LandingLocation;
	if (50.0f >= LocationDiff.Size())
	{
		StateChange(_OwnerComp, EMonsterState::Chase);
		return;
	}

	FRotator TurnRot = UKismetMathLibrary::FindLookAtRotation(MonsterLocation, LandingLocation);
	Monster->SetActorRotation(TurnRot);
}
