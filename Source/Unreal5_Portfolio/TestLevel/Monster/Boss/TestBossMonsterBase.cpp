// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/Boss/TestBossMonsterBase.h"

// Sets default values
ATestBossMonsterBase::ATestBossMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestBossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestBossMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

