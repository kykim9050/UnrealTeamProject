// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/MainGameInstance.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "Global/DataTable/NetDataRow.h"

UMainGameInstance::UMainGameInstance()
{

}

const FPlayerDataRow* UMainGameInstance::GetPlayerData(FName _Name)
{
	if (nullptr == PlayerDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerDataTable)"), __FUNCTION__, __LINE__);
	}

	FPlayerDataRow* Data = PlayerDataTable->FindRow<FPlayerDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const FNetDataRow* UMainGameInstance::GetNetData(FName _Name)
{
	if (nullptr == NetDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == NetDataTable)"), __FUNCTION__, __LINE__);
	}

	FNetDataRow* Data = NetDataTable->FindRow<FNetDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}
