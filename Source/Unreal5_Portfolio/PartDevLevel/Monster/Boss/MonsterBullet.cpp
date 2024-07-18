// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/MonsterBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMonsterBullet::AMonsterBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
    RootComponent = BulletMesh;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;

    BulletMesh->OnComponentHit.AddDynamic(this, &AMonsterBullet::OnHit);

    Damage = 10.0f;

}

// Called when the game starts or when spawned
void AMonsterBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Destroy();
}

