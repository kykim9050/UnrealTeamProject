// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/DoorObject.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"

ADoorObject::ADoorObject()
{

}

void ADoorObject::BeginPlay()
{
	Super::BeginPlay();
}

void ADoorObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorObject::SetMesh(FName _ObjName)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == Inst)"), __FUNCTION__, __LINE__);
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(_ObjName);
	GetMeshComponent()->SetStaticMesh(TableData->GetMesh());
}

void ADoorObject::Sliding()
{
	AddActorLocalOffset(FVector(0.0f, 100.0f, 0.0f));
}