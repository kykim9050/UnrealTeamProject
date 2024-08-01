// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCaptureCamera.h"

// Sets default values
ALobbyCaptureCamera::ALobbyCaptureCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALobbyCaptureCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALobbyCaptureCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALobbyCaptureCamera::SetCaptureLocation(int _PlayerNum)
{
	int _Y = (_PlayerNum + 1) * -100;
	SetActorLocation(FVector(200, _Y, 150));
}

