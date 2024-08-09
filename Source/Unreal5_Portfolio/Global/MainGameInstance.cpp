// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "Global/DataTable/NetDataRow.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/DataTable/BossMonsterDataRow.h"
#include "Global/DataTable/ItemDataRow.h"
#include "Global/DataTable/GlobalObjectRow.h"
#include "Global/DataTable/MapObjDataRow.h"
#include "Global/DataTable/QuestDataRow.h"

UMainGameInstance::UMainGameInstance()
{
	Random.GenerateNewSeed();
}

void UMainGameInstance::Init()
{
	Super::Init();

	// DT에서 UI 정보 불러오기

	// Title UI
	{
		if (nullptr == TitleUserWidgetDataTable)
		{
			LOG(UILog, Error, TEXT("TitleUserWidgetDataTable is nullptr"));
		}

		TArray<FWidgetDataRow*> Data;

		TArray<FName> Names = TitleUserWidgetDataTable->GetRowNames();
		TitleUserWidgetDataTable->GetAllRows(TEXT(""), Data);

		for (size_t i = 0; i < Data.Num(); ++i)
		{
			TitleWidgets.Add(Names[i].ToString(), *Data[i]);
		}
	}
	
	// InGame UI
	{
		if (nullptr == InGameUserWidgetDataTable)
		{
			LOG(UILog, Error, TEXT("InGameUserWidgetDataTable is nullptr"));
		}

		TArray<FWidgetDataRow*> Data;

		TArray<FName> Names = InGameUserWidgetDataTable->GetRowNames();
		InGameUserWidgetDataTable->GetAllRows(TEXT(""), Data);

		for (size_t i = 0; i < Data.Num(); ++i)
		{
			InGameWidgets.Add(Names[i].ToString(), *Data[i]);
		}
	}

	// Lobby UI
	{
		if (nullptr == LobbyUserWidgetDataTable)
		{
			LOG(UILog, Error, TEXT("LobbyUserWidgetDataTable is nullptr"));
		}

		TArray<FWidgetDataRow*> Data;

		TArray<FName> Names = LobbyUserWidgetDataTable->GetRowNames();
		LobbyUserWidgetDataTable->GetAllRows(TEXT(""), Data);

		for (size_t i = 0; i < Data.Num(); ++i)
		{
			LobbyWidgets.Add(Names[i].ToString(), *Data[i]);
		}
	}
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

const FBossMonsterDataRow* UMainGameInstance::GetBossMonsterData(FName _Name)
{
	if (nullptr == BossMonsterDataTable)
	{
		UE_LOG(MonsterLog, Fatal, TEXT("%S(%u)> if (nullptr == MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	FBossMonsterDataRow* Data = BossMonsterDataTable->FindRow<FBossMonsterDataRow>(_Name, nullptr);

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

const FWidgetDataRow* UMainGameInstance::GetInGameUserWidgetDataTable(FName _Name)
{
	if (nullptr == InGameUserWidgetDataTable)
	{
		UE_LOG(UILog, Fatal, TEXT("%S(%u)> if (nullptr == InGameUserWidgetDataTable)"), __FUNCTION__, __LINE__);
	}

	FWidgetDataRow* Data = InGameUserWidgetDataTable->FindRow<FWidgetDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(UILog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const FWidgetDataRow* UMainGameInstance::GetTitleUserWidgetDataTable(FName _Name)
{
	if (nullptr == TitleUserWidgetDataTable)
	{
		UE_LOG(UILog, Fatal, TEXT("%S(%u)> if (nullptr == TitleUserWidgetDataTable)"), __FUNCTION__, __LINE__);
	}

	FWidgetDataRow* Data = TitleUserWidgetDataTable->FindRow<FWidgetDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(UILog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const FWidgetDataRow* UMainGameInstance::GetLobbyUserWidgetDataTable(FName _Name)
{
	if (nullptr == LobbyUserWidgetDataTable)
	{
		UE_LOG(UILog, Fatal, TEXT("%S(%u)> if (nullptr == LobbyUserWidgetDataTable)"), __FUNCTION__, __LINE__);
	}

	FWidgetDataRow* Data = LobbyUserWidgetDataTable->FindRow<FWidgetDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(UILog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const TSubclassOf<UObject> UMainGameInstance::GetGlobalObjectClass(FName _Name)
{
	if (nullptr == GlobalObjectTable)
	{
		UE_LOG(GlobalLog, Fatal, TEXT("%S(%u)> if (nullptr == GlobalObjectTable)"), __FUNCTION__, __LINE__);
	}

	FGlobalObjectRow* Data = GlobalObjectTable->FindRow<FGlobalObjectRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(GlobalLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data->GetObject();
}

FMapObjDataRow* UMainGameInstance::GetMapObjDataTable(FName _Name)
{
	if (nullptr == MapObjDataTable)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == MapObjDataTable)"), __FUNCTION__, __LINE__);
	}

	FMapObjDataRow* Data = MapObjDataTable->FindRow<FMapObjDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(ObjectLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}

const FQuestDataRow* UMainGameInstance::GetQuestDataTable(FName _Name)
{
	if (nullptr == QuestDataTable)
	{
		UE_LOG(UILog, Fatal, TEXT("%S(%u)> if (nullptr == QuestDataTable)"), __FUNCTION__, __LINE__);
	}

	FQuestDataRow* Data = QuestDataTable->FindRow<FQuestDataRow>(_Name, nullptr);

	if (nullptr == Data)
	{
		UE_LOG(UILog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return Data;
}