// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Title/ConnectBrowserUserWidget.h"

#include "Global/MainGameInstance.h"

#include "Kismet/GameplayStatics.h"


void UConnectBrowserUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IPCombo->OnSelectionChanged.AddUniqueDynamic(this, &UConnectBrowserUserWidget::IPSelected);
	ConnectButton->OnClicked.AddUniqueDynamic(this, &UConnectBrowserUserWidget::Connect);

	IPComboDataInit();
}

void UConnectBrowserUserWidget::IPSelected(FString _IP, ESelectInfo::Type _SelectionType)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	if (nullptr == Inst)
	{
		return;
	}

	// FString¿¡¼­ IP ÆÄ½Ì
	FString Name;
	FString IP;
	{
		_IP.RemoveAt(0);
		_IP.RemoveAt(_IP.Len() - 1);

		_IP.Split(TEXT("]["), &Name, &IP);

		IPAddress = IP;
	}

	Inst->CurNetInfo.SetIP(IPAddress);
	Inst->CurNetInfo.SetPORT(Port);
}

void UConnectBrowserUserWidget::Connect()
{
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IPAddress, *Port);
	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName);
}

void UConnectBrowserUserWidget::IPComboDataInit()
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	UDataTable* IPTable = Inst->GetNetDataTable();
	TArray<FNetDataRow*> IPArr;
	IPTable->GetAllRows<FNetDataRow>(TEXT("GetAllRows"), IPArr);

	if (true == IPArr.IsEmpty())
	{
		return;
	}

	for (size_t i = 0; i < IPArr.Num(); ++i)
	{
		FNetDataRow* Data = IPArr[i];
		FString Option = FString::Printf(TEXT("[%s][%s]"), *Data->GetName(), *Data->GetIP());
		IPCombo->AddOption(Option);
	}

	IPCombo->SetSelectedIndex(0);
}