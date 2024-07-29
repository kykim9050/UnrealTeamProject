// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/Bomb.h"
#include "Global/ContentsLog.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MapObjDataRow.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "Kismet/GameplayStatics.h"


ABomb::ABomb()
{
}

void ABomb::CharacterToDestroy()
{
	this->Destroy();
}

void ABomb::SetInfo(FName _InfoName)
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

void ABomb::BeginPlay()
{
	Super::BeginPlay();
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (BombState::Install == CurBombState)
	{
		TimeFlow(DeltaTime);
	}
}

void ABomb::InterAction()
{
	Super::InterAction();

	if (BombState::Idle == CurBombState)
	{
		UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld())->AddArmoryWeaponNum(EPlayerPosture::Bomb);
		Destroy();
	}
}

void ABomb::TimeFlow(float _DeltaTime)
{
	BombTime -= _DeltaTime;
}
