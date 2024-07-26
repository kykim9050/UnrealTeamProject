// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Common/DefaultButtonUserWidget.h"
#include "Global/ContentsLog.h"
#include "Components/TextBlock.h"
#include "kismet/GameplayStatics.h"

void UDefaultButtonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonText->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UDefaultButtonUserWidget::SetButtonText(FText _text)
{
	ButtonText->SetText(_text);
}
