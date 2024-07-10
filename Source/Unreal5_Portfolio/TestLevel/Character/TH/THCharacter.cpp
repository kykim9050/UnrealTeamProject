// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Character/TH/THCharacter.h"

// Sets default values
ATHCharacter::ATHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATHCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

