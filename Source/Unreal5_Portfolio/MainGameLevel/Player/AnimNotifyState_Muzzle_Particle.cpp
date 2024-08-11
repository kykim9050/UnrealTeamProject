// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/AnimNotifyState_Muzzle_Particle.h"
#include "TestLevel/Character/TestCharacter.h"
#include "MainGameLevel/Player/MainCharacter.h"
#include "MainGameLevel/Player/PlayerItemInformation.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"

void UAnimNotifyState_Muzzle_Particle::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ATestCharacter* Player = MeshComp->GetOwner<ATestCharacter>();
	if (nullptr == Player)
	{
		return;
	}

	UArrowComponent* Position = nullptr;
	switch (Player->GetPointOfView())
	{
	case EPlayerFPSTPSState::TPS:
		Position = Player->MuzzlePos;
		break;
	case EPlayerFPSTPSState::FPS:
		Position = Player->FPVMuzzlePos;
		break;
	}
	FVector SpawnParticlePos = Position->GetComponentLocation();
	FRotator Rotate = FRotator::ZeroRotator;
	Rotate.Pitch = 90.0f;
	FVector Scale = FVector(1.0f, 1.0f, 1.0f);
	UWorld* World = Player->GetWorld();
	if (nullptr != World)
	{ 
		UGameplayStatics::SpawnEmitterAtLocation(World, Player->MuzzleEffect, SpawnParticlePos, Rotate, Scale, true);
	}
}

void UAnimNotifyState_Muzzle_Particle::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_Muzzle_Particle::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
