// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/SwitchObject.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"
#include "Components/CapsuleComponent.h"
//#include "MainGameLevel/Object/DoorObject.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "Kismet/GameplayStatics.h"


ASwitchObject::ASwitchObject()
{
}

void ASwitchObject::BeginPlay()
{
	Super::BeginPlay();

	//GetCollisionComponent()->AddRelativeLocation(CollisionOffset);
}

void ASwitchObject::SetInfo(FName _InfoName)
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

void ASwitchObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwitchObject::InterAction()
{
	Super::InterAction();

	AActor* OtherActor = UGameplayStatics::GetActorOfClass(GetWorld(), InteractObjClass);

	if (nullptr == OtherActor)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == OtherObj)"), __FUNCTION__, __LINE__);
		return;
	}

	// �ش� Ŭ���� ������ �ٿ�ĳ�����ϱ�
	AMapObjectBase* InteractObj = Cast<AMapObjectBase>(OtherActor);

	if (nullptr == InteractObj)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == InteractObj)"), __FUNCTION__, __LINE__);
		return;
	}

	InteractObj->InterAction();
}