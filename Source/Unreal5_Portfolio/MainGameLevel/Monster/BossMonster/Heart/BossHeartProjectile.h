// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossHeartProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class UNREAL5_PORTFOLIO_API ABossHeartProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossHeartProjectile();

public:
	FORCEINLINE void SetDamage(float Value)
	{
		Damage = Value;
	}

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BodyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USphereComponent* BodyCollision = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UProjectileMovementComponent* MovementComp = nullptr;

	float Damage = 0.0f;
};
