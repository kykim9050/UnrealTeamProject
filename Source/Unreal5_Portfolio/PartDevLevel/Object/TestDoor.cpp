// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
ATestDoor::ATestDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	Mesh->SetupAttachment(Collision);
		

}

// Called when the game starts or when spawned
void ATestDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestDoor::SlideDoorOpen(float _DeltaTime)
{

	if (false == IsDoorOpen)
	{
		if (MoveAmount < 0)
		{
			return;
		}

		AddActorLocalOffset(FVector(0.0f,60.0f,0.0f) * _DeltaTime);
		MoveAmount -= 60.f * _DeltaTime;
	}
	if (true == IsDoorOpen)
	{
		if (MoveAmount > 100)
		{
			return;
		}

		AddActorLocalOffset(FVector(0.0f, -60.0f, 0.0f) * _DeltaTime);
		MoveAmount += 60.f * _DeltaTime;
	}
}

void ATestDoor::RotationDoorOpen(float _DeltaTime)
{
	if (false == IsDoorOpen)
	{
		if (MoveAmount < 0)
		{
			return;
		}
		MoveAmount -= 30.f * _DeltaTime;
		AddActorLocalRotation(FRotator(0.f,-30.f,0.f) * _DeltaTime);
	}
	if (true == IsDoorOpen)
	{
		if (MoveAmount > 100)
		{
			return;
		}
		MoveAmount += 30.f * _DeltaTime;
		AddActorLocalRotation(FRotator(0.f, 30.f, 0.f) * _DeltaTime);
	}

}

