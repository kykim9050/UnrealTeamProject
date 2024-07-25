// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Title/ServerBtnUserWidget.h"
#include "MainGameLevel/UI/Title/MainTitleHUD.h"

#include "Global/ContentsLog.h"
#include "Global/MainGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UServerBtnUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ServerButton->OnClicked.AddUniqueDynamic(this, &UServerBtnUserWidget::OnServerButtonClicked);
	ConnectButton->OnClicked.AddUniqueDynamic(this, &UServerBtnUserWidget::OnConnectButtonClicked);

	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == MyController)
	{
		LOG(UILog, Fatal, "Controller is Null");
	}

	TitleHUD = Cast<AMainTitleHUD>(MyController->GetHUD());
	if (nullptr == TitleHUD)
	{
		LOG(UILog, Fatal, "Controller is Null");
	}
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

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TestLobbyLevel"));
}

void UServerBtnUserWidget::OnConnectButtonClicked()
{
	if (nullptr == TitleHUD)
	{
		LOG(UILog, Fatal, "Controller is Null");
	}
	TitleHUD->UISwitch(EUserWidgetType::TitleLogo);
	TitleHUD->UISwitch(EUserWidgetType::ServerBtn);

	TitleHUD->UISwitch(EUserWidgetType::ConnectBrowser);
}
