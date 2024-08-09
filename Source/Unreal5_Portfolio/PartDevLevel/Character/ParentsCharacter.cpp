// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/ParentsCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"


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

void AParentsCharacter::AnimationEnd()
{
}

void AParentsCharacter::AnimationEnd(FString _CurMontage)
{

}

void AParentsCharacter::ChangeHandAttackCollisionProfile(FName _Name)
{
	HandAttackComponent->SetCollisionProfileName(_Name);
}