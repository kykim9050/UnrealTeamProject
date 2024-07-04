// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestBrowserUserWidget.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ComboBoxString.h"

void UTestBrowserUserWidget::ServerStart()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		return;
	}

	Inst->CurNetInfo.SetIP(IPAddress);
	Inst->CurNetInfo.SetIsServer(true);
	Inst->CurNetInfo.SetPORT(Port);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TestLobbyLevel"));
}

void UTestBrowserUserWidget::Connect(FString _IP)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		return;
	}

	if (false == _IP.IsEmpty())
	{
		IPAddress = _IP;
	}

	Inst->CurNetInfo.SetIP(IPAddress);
	Inst->CurNetInfo.SetPORT(Port);

	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IPAddress, *Port);
	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName);
}

void UTestBrowserUserWidget::ServerInitialize(FName _RowName)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (true == _RowName.IsNone())
	{
		_RowName = FName("LocalNet");
	}
	const FNetDataRow* TempNetData = Inst->GetNetData(_RowName);
	IPAddress = TempNetData->GetIP();

	Inst->CurNetInfo.SetIP(IPAddress);
	Inst->CurNetInfo.SetPORT(Port);
}

void UTestBrowserUserWidget::IPComboDataInit(UDataTable* _IPData, UComboBoxString* _Combo)
{
	TArray<FNetDataRow*> IPArr;
	_IPData->GetAllRows<FNetDataRow>(TEXT("GetAllRows"), IPArr);

	if (true == IPArr.IsEmpty())
	{
		return;
	}

	for (size_t i = 0; i < IPArr.Num(); ++i)
	{
		FNetDataRow* Data = IPArr[i];
		FString Option = FString::Printf(TEXT("[%s][%s]"), *Data->GetName(), *Data->GetIP());
		//FString Option = FString::Printf(TEXT("%s"), *Data->GetName());
		_Combo->AddOption(Option);
	}

	_Combo->SetSelectedIndex(0);
}

void UTestBrowserUserWidget::IPComboSelectChange(FString _Text)
{
	_Text.RemoveAt(0);
	_Text.RemoveAt(_Text.Len() - 1);

	FString Name;
	FString IP;

	_Text.Split(TEXT("]["), &Name, &IP);

	IPAddress = IP;
}