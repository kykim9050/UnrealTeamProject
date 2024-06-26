// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterBase.h"

// Sets default values
ATestMonsterBase::ATestMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

