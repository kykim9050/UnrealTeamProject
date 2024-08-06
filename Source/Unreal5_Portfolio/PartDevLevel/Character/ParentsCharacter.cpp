// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/ParentsCharacter.h"

// Sets default values
AParentsCharacter::AParentsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParentsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParentsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

