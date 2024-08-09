// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Heart/BossHeartProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Global/ContentsLog.h"

#include "PartDevLevel/Character/ParentsCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

ABossHeartProjectile::ABossHeartProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BodyCollision"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));

	BodyCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossHeartProjectile::BeginOverlap);
}

void ABossHeartProjectile::BeginPlay()
{
	Super::BeginPlay();

	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bShouldBounce = false;
	MovementComp->InitialSpeed = 5000.f;
	MovementComp->MaxSpeed = 5000.f;

	MovementComp->Velocity = GetActorRotation().Vector().GetSafeNormal() * MovementComp->InitialSpeed;

	SetLifeSpan(1.5f);
}

void ABossHeartProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AParentsCharacter* HitCharacter = Cast<AParentsCharacter>(OtherActor);
	if (nullptr != HitCharacter)
	{
		ATestPlayerState* HitPlayerState = HitCharacter->GetPlayerState<ATestPlayerState>();
		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
			return;
		}

		if (0.0f < HitPlayerState->GetPlayerHp())
		{
			HitPlayerState->AddDamage(Damage);
		}
	}
}

