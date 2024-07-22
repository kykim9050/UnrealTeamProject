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

	if (true == SlideDoorOpen)
	{
		Sliding(DeltaTime);
	}
	else if(true == RotateDoorOpen)
	{
		Rotating(DeltaTime);
	}
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

void ADoorObject::Sliding(float _DeltaTime)
{
	//AddActorLocalOffset(FVector(0.0f, 100.0f, 0.0f));
	//if (false == IsDoorOpen)
	//{
	//	if (MoveAmount < 0)
	//	{
	//		return;
	//	}

	//	AddActorLocalOffset(FVector(0.0f, 60.0f, 0.0f) * _DeltaTime);
	//	MoveAmount -= 60.f * _DeltaTime;
	//}

	if (MoveAmount > 200)
	{
		return;
	}

	AddActorLocalOffset(FVector(-60.0f, 0.0f, 0.0f) * _DeltaTime);
	MoveAmount += 60.f * _DeltaTime;
}

void ADoorObject::Rotating(float _DeltaTime)
{
	if (MoveAmount > 150)
	{
		return;
	}
	MoveAmount += 30.f * _DeltaTime;
	AddActorLocalRotation(FRotator(0.f, 30.f, 0.f) * _DeltaTime);
}

void ADoorObject::InterAction()
{
	Super::InterAction();

	switch (Type)
	{
	case EDoorType::Silding:
		SlideDoorOpen = true;
		break;
	case EDoorType::Rotating:
		RotateDoorOpen = true;
		break;
	default:
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> EDoorType Type = EDoorType::None"), __FUNCTION__, __LINE__);
		return;
	}
}