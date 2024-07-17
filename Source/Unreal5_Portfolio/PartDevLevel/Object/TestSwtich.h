// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestSwtich.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ATestSwtich : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestSwtich();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DoorSwitch(AActor* _OtherActor);


	void GetDoorTime()
	{
		DoorTime;
	}

	void SetDoorTime()
	{
		DoorTime = 0.0f;
	}


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Collision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ATestDoor* ConnectedDoor = nullptr;

	UFUNCTION(BlueprintCallable)
	void CharactorCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	bool CharctorOn = false;

	float DoorTime = 0.0f;
};
