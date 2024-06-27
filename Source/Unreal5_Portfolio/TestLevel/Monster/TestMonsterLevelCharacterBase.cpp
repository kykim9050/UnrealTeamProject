// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterLevelCharacterBase.h"

// Sets default values
ATestMonsterLevelCharacterBase::ATestMonsterLevelCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMonsterLevelCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMonsterLevelCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestMonsterLevelCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

