// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestLobbyUI.h"
#include "Global/MainGameInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"

void UTestLobbyUI::TravelToNext()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		GetWorld()->ServerTravel("/Game/Resources/TestLevel/TestPlayLevel");
	}
}

bool UTestLobbyUI::IsServer()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	return Inst->CurNetInfo.GetIsServer();
}