// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestTitleUI.h"
#include "Global/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTestTitleUI::ServerStart()
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();

	if (nullptr == Inst)
	{
		return;
	}

	Inst->CurNetInfo.SetIsServer(true);
	Inst->CurNetInfo.SetPORT(Port);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TestLobbyLevel"));
}

void UTestTitleUI::Connect(FString _IP)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();

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

bool UTestTitleUI::Initialize()
{
	bool ReturnValue = Super::Initialize();

	IPAddress = TEXT("127.0.0.1");

	return ReturnValue;
}

void UTestTitleUI::ServerTest(FName _IPName)
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	if (true == _IPName.IsNone())
	{
		_IPName = FName("LocalNet");
	}
	Test = Inst->GetNetData(_IPName);
	IPAddress = Test->GetIP();

	Inst->CurNetInfo.SetIP(IPAddress);
	Inst->CurNetInfo.SetPORT(Port);
}

