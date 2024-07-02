// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "Global/DataTable/NetDataRow.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/DataTable/ItemDataRow.h"

UMainGameInstance::UMainGameInstance()
{

}

const FPlayerDataRow* UMainGameInstance::GetPlayerData(FName _Name)
{
	if (nullptr == PlayerDataTable)
	{
		UE_LOG(PlayerLog, Fatal, TEXT("%S(%u)> if (nullptr == PlayerDataTable)"), __FUNCTION__, __LINE__);
	}

	FPlayerDataRow* Data = PlayerDataTable->FindRow<FPlayerDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(PlayerLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
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

const FMonsterDataRow* UMainGameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterDataTable)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("%S(%u)> if (nullptr == MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	FMonsterDataRow* Data = MonsterDataTable->FindRow<FMonsterDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(MonsterLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const FItemDataRow* UMainGameInstance::GetItemData(FName _Name)
{
	if (nullptr == ItemDataTable)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == ItemDataTable)"), __FUNCTION__, __LINE__);
	}

	FItemDataRow* Data = ItemDataTable->FindRow<FItemDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(ObjectLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}