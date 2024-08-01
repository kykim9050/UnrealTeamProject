// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Particles/MuzzleParticleActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMuzzleParticleActor::AMuzzleParticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	MuzzleParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleParticle"));
	MuzzleParticleComponent->SetupAttachment(RootComponent);
	
	//MuzzleParticleComponent->SetIsReplicated(true);
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticleComponent, GetTransform(), false, EPSCPoolMethod::None, false);
}

// Called when the game starts or when spawned
void AMuzzleParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
	CalLifeTime = 0.0f;
	MuzzleParticleComponent->SetVisibleFlag(true);

}

// Called every frame
void AMuzzleParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//DestroyTime(DeltaTime);
}

void AMuzzleParticleActor::DestroyTime(float _DeltaTime)
{
	CalLifeTime += _DeltaTime;
	if (CalLifeTime >= LifeTime)
	{
		this->Destroy();
	}
}

