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
	BombMesh->SetupAttachment(RootComponent);
}

void AAreaObject::BeginPlay()
{
	Super::BeginPlay();

	FName Name = FName(TEXT("Area"));
	SetInfo(Name);

	PlantingSpotCollision->SetRelativeLocation(FVector(450.0f, 0.0f, 225.0f));
}

void AAreaObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAreaObject::InterAction()
{
	Super::InterAction();

	FName InfoName = FName(TEXT("Bomb"));

	BombPlanting(InfoName);
	//if (0.0f >= BombInstallTime)
	//{
	//	BombInstallTime = 3.0f;
	//	BombPlanting();
	//}
}

void AAreaObject::BombPlanting(FName _InfoName)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		LOG(ObjectLog, Fatal, "if (nullptr == Inst)");
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(_InfoName);
	BombMesh->SetStaticMesh(TableData->GetMesh());
}