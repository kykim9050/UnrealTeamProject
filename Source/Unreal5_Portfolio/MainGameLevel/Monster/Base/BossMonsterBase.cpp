// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Base/BossMonsterBase.h"

// Sets default values
ABossMonsterBase::ABossMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

