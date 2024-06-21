// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestTitleUI.h"
#include "Global/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

//void UTestTitleUI::ServerStart()
//{
//	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
//
//	if (nullptr == Inst)
//	{
//		return;
//	}
//
//	Inst->MyTestGameInfo.IsServer = true;
//	Inst->MyTestGameInfo.PORT = Port;
//
//	UGameplayStatics::OpenLevel(GetWorld(), TEXT("LobbyLevel"));
//}
//
//void UTestTitleUI::Connect(FString _IP)
//{
//	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
//
//	if (nullptr == Inst)
//	{
//		return;
//	}
//
//	Inst->MyTestGameInfo.IP = _IP;
//	Inst->MyTestGameInfo.PORT = Port;
//
//	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IPAddress, *Port);
//	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName);
//}

bool UTestTitleUI::Initialize()
{
	bool ReturnValue = Super::Initialize();

	IPAddress = TEXT("127.0.0.1");

	return ReturnValue;
}
