// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestLobbyUI.h"
#include "Global/MainGameInstance.h"

void UTestLobbyUI::TravelToNext()
{
	UMainGameInstance* Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		GetWorld()->ServerTravel("/Game/Resources/TestLevel/TestPlayLevel");
	}
}

bool UTestLobbyUI::IsServer()
{
	UMainGameInstance* Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	return Inst->CurNetInfo.GetIsServer();
}