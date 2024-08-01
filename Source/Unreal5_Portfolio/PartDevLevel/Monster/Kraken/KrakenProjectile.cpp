// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Kraken/KrakenProjectile.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "Global/ContentsLog.h"

// Sets default values
AKrakenProjectile::AKrakenProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjcetileCollision"));
	RootComponent = ProjectileCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	ProjectileCollisionRadius = 50.0f;
	ProjectileCollision->InitSphereRadius(ProjectileCollisionRadius);

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AKrakenProjectile::BeginOverlap);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(ProjectileMesh);
}

// Called when the game starts or when spawned
void AKrakenProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileCollision->SetSphereRadius(ProjectileCollisionRadius);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation());
}

void AKrakenProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKrakenProjectile, Hp);
	//DOREPLIFETIME(AKrakenProjectile, AniIndex);
}

void AKrakenProjectile::Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestCharacter* HitCharacter = Cast<ATestCharacter>(_OtherActor);
	if (nullptr != HitCharacter)
	{
		ATestPlayerState* HitPlayerState = Cast<ATestPlayerState>(HitCharacter->GetPlayerState());
		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
		}

		HitPlayerState->AddDamage(Damage);
		OnDead();
	}
}

void AKrakenProjectile::Damaged(float _Damage)
{
	if (false == HasAuthority() || 0.0f >= Hp)
	{
		return;
	}

	Hp -= _Damage;

	if (0.0f >= Hp)
	{
		OnDead();
	}
}

// Called every frame
void AKrakenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::ZeroVector == ProjectileMovement->Velocity)
	{
		/*if (true == HasAuthority())
		{*/
			ParticleSystemComponent->SetActive(false);
			if (false == IsParticleChange)
			{
				IsParticleChange = true;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GroundParticle, ParticleSystemComponent->GetComponentLocation());
			}
		//}

		ProjectileCollision->SetCollisionProfileName(FName("KrakenRockStop"));
	}
	else
	{
		FRotator Rotate;
		Rotate.Roll = DeltaTime * RotateSpeed;
		Rotate.Yaw = DeltaTime * RotateSpeed;
		Rotate.Pitch = DeltaTime * RotateSpeed;
		RootComponent->AddLocalRotation(Rotate);
	}
}

void AKrakenProjectile::SetDirection(FVector Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed + GetActorUpVector() * UpSpeed;
}

void AKrakenProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Attack(OtherActor, OtherComp);
}

void AKrakenProjectile::OnDead()
{
	ParticleSystemComponent->SetActive(false);
	SetOnDead();
	Destroy();
}

void AKrakenProjectile::SetOnDead_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform());
}
