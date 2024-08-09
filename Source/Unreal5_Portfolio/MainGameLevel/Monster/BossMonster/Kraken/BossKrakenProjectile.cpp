// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "Global/ContentsLog.h"

#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

ABossKrakenProjectile::ABossKrakenProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BodyCollision"));
	BodyCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossKrakenProjectile::BeginOverlap);
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bShouldBounce = false;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(BodyMesh);
}

void ABossKrakenProjectile::BeginPlay()
{
	Super::BeginPlay();

	StateChange(BossKraKenProjectile::EState::Fly);
}

void ABossKrakenProjectile::Tick(float DeltaTimes)
{
	Super::Tick(DeltaTimes);

	StateUpdate(DeltaTimes);
}

void ABossKrakenProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABossKrakenProjectile, Hp);
}

void ABossKrakenProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATestCharacter* HitCharacter = Cast<ATestCharacter>(OtherActor);
	if (nullptr != HitCharacter)
	{
		ATestPlayerState* HitPlayerState = HitCharacter->GetPlayerState<ATestPlayerState>();
		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
			return;
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CrashParticle, GetActorTransform());
		if (BossKraKenProjectile::EState::Fly == CurState)
		{
			HitPlayerState->AddDamage(Damage);
		}
		
		Destroy();
	}
}

void ABossKrakenProjectile::Fly(float DeltaTimes)
{
	if (FVector::ZeroVector == MovementComp->Velocity)
	{
		StateChange(BossKraKenProjectile::EState::Stop);
	}
}

void ABossKrakenProjectile::FlyStart()
{
	FVector Dir = (GetActorRotation().Vector() + GetActorUpVector()).GetSafeNormal();
	MovementComp->Velocity = MovementComp->InitialSpeed * Dir;
}

void ABossKrakenProjectile::StopStart()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CrashParticle, GetActorTransform());
	BodyCollision->SetCollisionProfileName(FName("KrakenRockStop"));
	ParticleSystemComponent->SetActive(false);
	SetLifeSpan(LifeTime);
}

void ABossKrakenProjectile::StateUpdate(float DeltaTimes)
{
	switch (CurState)
	{
	case BossKraKenProjectile::EState::Fly:
		Fly(DeltaTimes);
		break;
	case BossKraKenProjectile::EState::Stop:
		Stop(DeltaTimes);
		break;
	}
}

void ABossKrakenProjectile::StateChange(BossKraKenProjectile::EState NextState)
{
	if (NextState != CurState)
	{
		switch (NextState)
		{
		case BossKraKenProjectile::EState::Fly:
			FlyStart();
			break;
		case BossKraKenProjectile::EState::Stop:
			StopStart();
			break;
		}

		CurState = NextState;
	}
}