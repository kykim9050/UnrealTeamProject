// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Title/ServerBtnUserWidget.h"
#include "MainGameLevel/UI/Title/MainTitleHUD.h"

#include "Global/ContentsLog.h"
#include "Global/MainGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"


void UServerBtnUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 시 실행 함수 묶어줌
	SetNameButton->DefaultButton->OnClicked.AddUniqueDynamic(this, &UServerBtnUserWidget::OnSetNameButtonClicked);
	ServerButton->DefaultButton->OnClicked.AddUniqueDynamic(this, &UServerBtnUserWidget::OnServerButtonClicked);
	ConnectButton->DefaultButton->OnClicked.AddUniqueDynamic(this, &UServerBtnUserWidget::OnConnectButtonClicked);

	// 버튼 텍스트 설정
	SetNameButton->SetButtonText(FText::FromString(FString("Setting")));
	ServerButton->SetButtonText(FText::FromString(FString("Game Start")));
	ConnectButton->SetButtonText(FText::FromString(FString("Connect")));
	
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == MyController)
	{
		LOG(UILog, Fatal, "Controller is Null");
	}

	TitleHUD = Cast<AMainTitleHUD>(MyController->GetHUD());
	if (nullptr == TitleHUD)
	{
		LOG(UILog, Fatal, "HUD is Null");
	}
}

void UServerBtnUserWidget::OnSetNameButtonClicked()
{
	TitleHUD->UIOff(EUserWidgetType::ServerBtn);
	TitleHUD->UIOn(EUserWidgetType::SettingBrowser);
}

void UServerBtnUserWidget::OnServerButtonClicked()
{
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();

	if (nullptr == Inst)
	{
		return;
	}

	Inst->CurNetInfo.SetIsServer(true);
	Inst->CurNetInfo.SetPORT(Port);

	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("TestLobbyLevel"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLobbyLevel"));
}

void UServerBtnUserWidget::OnConnectButtonClicked()
{
	if (nullptr == TitleHUD)
	{
		LOG(UILog, Fatal, "TitleHUD is Null");
	}

	TitleHUD->UISwitch(EUserWidgetType::ServerBtn);
	TitleHUD->UISwitch(EUserWidgetType::ConnectBrowser);
}

void UServerBtnUserWidget::SetMainNicknameUI(FText _Myname)
{
	MainNickname->SetText(_Myname);
}
