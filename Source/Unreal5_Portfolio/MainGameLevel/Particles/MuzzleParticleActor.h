// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MuzzleParticleActor.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMuzzleParticleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMuzzleParticleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	UFUNCTION()
	void DestroyTime(float _DeltaTime);

private :
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* MuzzleParticleComponent = nullptr;

	UPROPERTY()
	float LifeTime = 0.2;

	UPROPERTY()
	float CalLifeTime = 0.0f;
};
