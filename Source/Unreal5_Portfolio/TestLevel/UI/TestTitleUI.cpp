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

	Inst->CurNetInfo.SetIP(_IP);
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
