// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/MapObjectBase.h"
#include "Components/CapsuleComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"

// Sets default values
AMapObjectBase::AMapObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MapObjCollision"));
	SetRootComponent(CollisionComponent);
	//CollisionComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapObjMesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AMapObjectBase::SetInfo(FName _InfoName)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == Inst)"), __FUNCTION__, __LINE__);
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(_InfoName);
	GetMeshComponent()->SetStaticMesh(TableData->GetMesh());

	InteractObjClass = TableData->GetInteractObjClass();
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