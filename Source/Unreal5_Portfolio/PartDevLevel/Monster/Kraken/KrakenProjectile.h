// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KrakenProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class UNREAL5_PORTFOLIO_API AKrakenProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKrakenProjectile();
	void Damaged(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDirection(FVector Direction);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void OnDead();

	UFUNCTION(Reliable, NetMulticast)
	void SetOnDead();
	void SetOnDead_Implementation();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USphereComponent* ProjectileCollision;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* DestroyParticle;
	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* GroundParticle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileCollisionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateSpeed = 0.0f;

	UPROPERTY(Replicated)
	float Hp = 100.0f;
};
