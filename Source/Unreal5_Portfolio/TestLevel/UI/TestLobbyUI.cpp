// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestLobbyUI.h"
#include "Global/MainGameInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"

void UTestLobbyUI::TravelToNext()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		bool CanTravel = GetWorld()->ServerTravel("/Game/Resources/MainGameLevel/LandscapePreview");
		//bool CanTravel = GetWorld()->ServerTravel("/Game/Resources/TestLevel/TestPlayLevel");
		int a = 0;
	}
}

bool UTestLobbyUI::IsServer()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	return Inst->CurNetInfo.GetIsServer();
}