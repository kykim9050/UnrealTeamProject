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

void AAreaObject::InterAction()
{
	Super::InterAction();


	if (0.0f >= InstallBombTime)
	{
		InstallBombTime = 3.0f;
		FName InfoName = FName(TEXT("Bomb"));
		BombPlanting(InfoName);
	}
}

void AAreaObject::BombPlanting_Implementation(FName _InfoName)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		LOG(ObjectLog, Fatal, "if (nullptr == Inst)");
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(_InfoName);
	BombMesh->SetStaticMesh(TableData->GetMesh());
	BombMesh->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	//PlantingSpotCollision->SetActive(false);

	if (true == HasAuthority())
	{
		AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());

		if (nullptr == MainGameState)
		{
			return;
		}

		MainGameState->SetPlantingBombComplete();
	}
}

void AAreaObject::InstallBomb(float _DeltaTime)
{
	InstallBombTime -= _DeltaTime;
}