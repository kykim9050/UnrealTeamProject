// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDoor.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ATestDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDoor();

	bool GetIsDoorOpen()
	{
		return IsDoorOpen;
	}

	void SetIsDoorOpen(bool _IsOpen)
	{
		IsDoorOpen = _IsOpen;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsDoorOpen = false;
	float MoveAmount = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Collision = nullptr;

	UFUNCTION(BlueprintCallable)
	void SlideDoorOpen(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void RotationDoorOpen(float DeltaTime);


};
