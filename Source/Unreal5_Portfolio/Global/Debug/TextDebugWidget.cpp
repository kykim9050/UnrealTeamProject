// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Debug/TextDebugWidget.h"
#include "Components/TextBlock.h"
#include "Global/ContentsLog.h"

void UTextDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DebugText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DebugText")));

	if (nullptr == DebugText)
	{
		UE_LOG(UILog, Fatal, TEXT("%s(%u)> if (nullptr == DebugText)"), __FUNCTION__, __LINE__);
		return;
	}
}

void UTextDebugWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

	DebugText->SetText(FText::FromString(AllDebugText));
	AllDebugText = TEXT("");
}

void UTextDebugWidget::AddDebugString(FString _Text)
{
	AllDebugText += _Text + TEXT("\n");
}