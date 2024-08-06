// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/HeadNameUserWidget.h"
#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UHeadNameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	//if (nullptr == MainGameInst)
	//{
	//	LOG(UILog, Fatal, "MainGameInstance is Null");
	//	return;
	//}
	//
	//SetNameText(FText::FromString(MainGameInst->GetMainNickName()));
}

void UHeadNameUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);
}

void UHeadNameUserWidget::SetNameText(FText _Nickname)
{
	NameText->SetText(_Nickname);
}

