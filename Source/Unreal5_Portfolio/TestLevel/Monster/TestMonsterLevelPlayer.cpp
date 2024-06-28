// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterLevelPlayer.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsEnum.h"

// Sets default values
ATestMonsterLevelPlayer::ATestMonsterLevelPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMonsterLevelPlayer::BeginPlay()
{
	Super::BeginPlay();
	UMainGameBlueprintFunctionLibrary::PushActor(GetWorld(), EObjectType::Player, this);	
}

// Called every frame
void ATestMonsterLevelPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestMonsterLevelPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

