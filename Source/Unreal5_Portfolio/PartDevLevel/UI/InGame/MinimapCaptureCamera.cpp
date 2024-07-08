// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/UI/InGame/MinimapCaptureCamera.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestCharacter.h"

// Sets default values
AMinimapCaptureCamera::AMinimapCaptureCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinimapCaptureCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinimapCaptureCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATestCharacter* MyCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FVector CharacterPos = MyCharacter->GetActorLocation();
	SetActorLocation(CharacterPos);
}

