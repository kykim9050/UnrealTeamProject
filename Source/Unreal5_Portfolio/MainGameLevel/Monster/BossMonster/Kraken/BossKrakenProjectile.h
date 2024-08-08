// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossKrakenProjectile.generated.h"

class UParticleSystem;
class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

namespace BossKraKenProjectile
{
	enum class EState
	{
		Fly,
		Stop,
		Max
	};
}

UCLASS()
class UNREAL5_PORTFOLIO_API ABossKrakenProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABossKrakenProjectile();

	FORCEINLINE void SetDamage(float Value)
	{
		Damage = Value;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimes) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void StateUpdate(float DeltaTimes);
	void StateChange(BossKraKenProjectile::EState NextState);

	void Fly(float DeltaTimes);
	void FlyStart();

	void Stop(float DeltaTimes) {};
	void StopStart();

private:
	// Data
	UPROPERTY(Replicated, EditAnywhere, Category = "SettingData", meta = (AllowPrivateAccess = true))
	float Hp = 100.0f;
	float Damage = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = "SettingData", meta = (AllowPrivateAccess = true))
	float LifeTime = 0.0f;

	
	BossKraKenProjectile::EState CurState = BossKraKenProjectile::EState::Max;

private:
	// Component
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USphereComponent* BodyCollision = nullptr;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BodyMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* MovementComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* CrashParticle = nullptr;

};
