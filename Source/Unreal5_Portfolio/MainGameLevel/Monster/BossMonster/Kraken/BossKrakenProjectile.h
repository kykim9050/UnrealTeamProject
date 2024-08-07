// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossKrakenProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class UNREAL5_PORTFOLIO_API ABossKrakenProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABossKrakenProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimes) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
private:
	// Data
	UPROPERTY(Replicated)
	float Hp = 100.0f;

private:
	// Component
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USphereComponent* BodyCollision = nullptr;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BodyMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* MovementComp = nullptr;

};
