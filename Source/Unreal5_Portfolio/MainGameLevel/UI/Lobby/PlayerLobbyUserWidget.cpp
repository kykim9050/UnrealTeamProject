// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/PlayerLobbyUserWidget.h"
#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"
#include "MainGameLevel/UI/Lobby/PlayerViewUserWidget.h"
#include "MainGameLevel/UI/Lobby/CharacterSelectionUserWidget.h"
#include "MainGameLevel/UI/Title/ServerBtnUserWidget.h"
#include "MainGameLevel/UI/Lobby/MainLobbyHUD.h"
#include "MainGameLevel/LobbyGameMode.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

#include "Kismet/GameplayStatics.h"

void UPlayerLobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 시 실행 함수 묶어줌
	B_Ready->DefaultButton->OnClicked.AddUniqueDynamic(this, &UPlayerLobbyUserWidget::OnReadyBtn);
	B_Start->DefaultButton->OnClicked.AddUniqueDynamic(this, &UPlayerLobbyUserWidget::OnStartBtn);

	// 버튼 텍스트 설정
	B_Ready->SetButtonText(FText::FromString(FString("Ready")));
	B_Start->SetButtonText(FText::FromString(FString("Start")));

	AGameModeBase* IsServer = GetWorld()->GetAuthGameMode();
	if (nullptr == IsServer)
	{
		// Client
		ReadybtnVisibility(true);
		StartbtnVisibility(false);
	}
	else
	{
		// Server
		ReadybtnVisibility(false);
		StartbtnVisibility(true);
	}
}

void UPlayerLobbyUserWidget::ReadybtnVisibility(bool _On)
{
	if (true == _On)
	{
		B_Ready->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		B_Ready->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayerLobbyUserWidget::StartbtnVisibility(bool _On)
{
	if (true == _On)
	{
		B_Start->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		B_Start->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayerLobbyUserWidget::OnReadyBtn()
{
	ALobbyCharacter* MyLobbyCharacter = Cast<ALobbyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr == MyLobbyCharacter)
	{
		LOG(UILog, Fatal, "LobbyCharacter is Null. (Or NetMode : Need StandAlone)");
	}
	MyLobbyCharacter->ReadyClicked = true;
	B_Ready->SetIsEnabled(false);
}

void UPlayerLobbyUserWidget::OnStartBtn()
{
	AGameModeBase* IsServer = GetWorld()->GetAuthGameMode();
	if (IsServer == nullptr)
	{
		LOG(UILog, Fatal, "This is ServerButton but AGameModeBase is Null.");
	}
	ALobbyGameMode* lobby = Cast<ALobbyGameMode>(IsServer);

	int RCount = lobby->GetReadyCount();
	int PCount = lobby->GetPlayerCount();

	//APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//AMainLobbyHUD* lobbyHUD = nullptr;
	//if (nullptr != Con)
	//{
	//	lobbyHUD = Cast<AMainLobbyHUD>(Con->GetHUD());
	//	if (nullptr == lobbyHUD)
	//	{
	//		LOG(UILog, Fatal, "lobbyHUD is Null.");
	//	}
	//}

	if (RCount == PCount - 1)
	{
		// 모두 준비 함
		//lobbyHUD->UIOff(EUserWidgetType::CantStart);
		// 게임으로 이동
		TravelToNext();
	}
	else
	{
		// 시작할 수 없음.
		//lobbyHUD->UIOn(EUserWidgetType::CantStart);
		int a = 0;
	}
}

void UPlayerLobbyUserWidget::TravelToNext()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		bool CanTravel = GetWorld()->ServerTravel("/Game/Resources/MainGameLevel/LandscapePreview");
		//bool CanTravel = GetWorld()->ServerTravel("/Game/Resources/TestLevel/TestPlayLevel");
	}
}

bool UPlayerLobbyUserWidget::IsServer()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	return Inst->CurNetInfo.GetIsServer();
}
