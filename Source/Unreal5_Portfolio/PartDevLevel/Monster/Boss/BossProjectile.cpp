// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/BossProjectile.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Global/ContentsLog.h"

// Sets default values
ABossProjectile::ABossProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileColComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Projcetilecol Comp"));
	RootComponent = ProjectileColComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// 콜리전 크기 초기 값
	ProjectileCollisionRadius = 50.0f;
	ProjectileColComponent->InitSphereRadius(ProjectileCollisionRadius);

	ProjectileColComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossProjectile::BeginOverlap);

	SetLifeSpan(3.0f);
}

// Called when the game starts or when spawned
void ABossProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileColComponent->SetSphereRadius(ProjectileCollisionRadius);
}

void ABossProjectile::Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{

	ATestCharacter* HitCharacter = Cast<ATestCharacter>(_OtherActor);
	ATestPlayerState* HitPlayerState = Cast<ATestPlayerState>(HitCharacter->GetPlayerState());
	
	if (nullptr == HitPlayerState)
	{
		LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
	}

	HitPlayerState->AddDamage(ProjectileDamage);
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

void ABossProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 총알이 플레이어와 충돌했을 때 파괴
	if (OtherActor->IsA(ATestCharacter::StaticClass()))
	{
		Attack(OtherActor, OtherComp);
		// 충돌한 액터가 플레이어인지 확인 후 파괴
		Destroy();
	}
}

