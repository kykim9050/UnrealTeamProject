// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Title/SettingBrowserUserWidget.h"
#include "MainGameLevel/UI/Title/MainTitleHUD.h"
#include "MainGameLevel/UI/Title/ServerBtnUserWidget.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"

#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void USettingBrowserUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 시 실행 함수 묶어줌
	OkButton->DefaultButton->OnClicked.AddUniqueDynamic(this, &USettingBrowserUserWidget::OnOkButtonClicked);

	// 버튼 텍스트 설정
	OkButton->SetButtonText(FText::FromString(FString("Ok")));
}

void USettingBrowserUserWidget::OnOkButtonClicked()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == MyController)
	{
		LOG(UILog, Fatal, "Controller is Null");
	}

	AMainTitleHUD* TitleHUD = Cast<AMainTitleHUD>(MyController->GetHUD());
	if (nullptr == TitleHUD)
	{
		LOG(UILog, Fatal, "HUD is Null");
	}

	// 세팅값들을 MainGameInstance에 저장 
	FText text = NameTextBox->GetText();
	Inst->SetMainNickName(text.ToString()); // 닉네임 

	// 창 닫기 
	TitleHUD->UIOff(EUserWidgetType::SettingBrowser);
	TitleHUD->UIOn(EUserWidgetType::ServerBtn);

	// 타이틀에 보여주기 
	Cast<UServerBtnUserWidget>(TitleHUD->GetWidget(EUserWidgetType::ServerBtn))->SetMainNicknameUI(text);
}
