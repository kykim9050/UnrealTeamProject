// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/BossMonster/Kraken/BossKrakenProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

ABossKrakenProjectile::ABossKrakenProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BodyCollision"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bShouldBounce = false;

}

void ABossKrakenProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ABossKrakenProjectile::Tick(float DeltaTimes)
{
	Super::Tick(DeltaTimes);

}

void ABossKrakenProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABossKrakenProjectile, Hp);
}