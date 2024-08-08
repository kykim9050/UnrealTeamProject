// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/UI/HUD/Timer_UserWidget.h"

void UTimer_UserWidget::SetTimerCurStage(EGameStage _SetStage)
{
	AMainGameState* WidgetGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
	WidgetGameState->SetCurStage(_SetStage);
}

void UTimer_UserWidget::SetTime(int _Hour, int _Min, int _Second)
{
	NowTimeSpan = FTimespan(_Hour,_Min,_Second);
	FText TextTemplate = FText::FromString("{_Hour}:{_Min}:{_Second}");

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("_Hour"), FText::AsNumber(_Hour));
	Arguments.Add(TEXT("_Min"), FText::AsNumber(_Min));
	Arguments.Add(TEXT("_Second"), FText::AsNumber(_Second));
}

void UTimer_UserWidget::SetTime(int _Min, int _Second)
{
	NowTimeSpan = FTimespan(0,_Min,_Second);
}
