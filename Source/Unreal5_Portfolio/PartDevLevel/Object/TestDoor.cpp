// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestDoor.h"

// Sets default values
ATestDoor::ATestDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

