// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/MapObjectBase.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AMapObjectBase::AMapObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MapObjCollision"));
	SetRootComponent(Collision);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapObjMesh"));
	MeshComponent->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AMapObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

