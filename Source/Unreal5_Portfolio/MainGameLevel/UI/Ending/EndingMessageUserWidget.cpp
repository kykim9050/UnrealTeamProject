// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Ending/EndingMessageUserWidget.h"

void UEndingMessageUserWidget::AddEndingCredit(FText _Text)
{
	EndingCreditArr.Add(_Text);
}
