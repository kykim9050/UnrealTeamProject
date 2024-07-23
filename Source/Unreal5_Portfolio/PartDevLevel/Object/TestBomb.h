// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestBomb.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ATestBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Collision = nullptr;

	UFUNCTION(BlueprintCallable)
	void CharactorCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	void BombActivation(float _DeltaTime);

	bool CharctorOn = false;

	float BombTime = 0.f;

};
