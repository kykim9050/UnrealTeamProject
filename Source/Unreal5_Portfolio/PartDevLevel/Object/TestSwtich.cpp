// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestSwtich.h"
#include "Components/BoxComponent.h"


// Sets default values
ATestSwtich::ATestSwtich()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	Mesh->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchCollision"));
	Collision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestSwtich::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestSwtich::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

