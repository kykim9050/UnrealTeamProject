// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/AreaObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"

AAreaObject::AAreaObject()
{
	PlantingSpotCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlantingSpotCollision"));
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));

	PlantingSpotCollision->SetupAttachment(RootComponent);
	BombMesh->SetupAttachment(PlantingSpotCollision);

	BombMesh->SetIsReplicated(true);
}

void AAreaObject::BeginPlay()
{
	Super::BeginPlay();

	FName Name = FName(TEXT("Area"));
	SetInfo(Name);

	PlantingSpotCollision->SetRelativeLocation(FVector(450.0f, 0.0f, 235.0f));
	PlantingSpotCollision->SetCollisionProfileName(FName(TEXT("MapItem")));
}

void AAreaObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAreaObject::InstallBomb(float _DeltaTime)
{
	InstallBombTime -= _DeltaTime;
}