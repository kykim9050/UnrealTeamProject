// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/BossProjectile.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABossProjectile::ABossProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	// RootComponent = ProjectileMesh;

	ProjectileColComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Projcetilecol Comp"));
	ProjectileColComponent->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

}

// Called when the game starts or when spawned
void ABossProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

void ABossProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// 총알이 플레이어와 충돌했을 때 파괴
	if (OtherActor->IsA(ATestCharacter::StaticClass()))
	{
		// 충돌한 액터가 플레이어인지 확인 후 파괴
		Destroy();
	}
}

