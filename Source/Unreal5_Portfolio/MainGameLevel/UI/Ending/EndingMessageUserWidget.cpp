// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Ending/EndingMessageUserWidget.h"

void UEndingMessageUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//EndingCreditArr.Add(FText::FromString(FString("TEAM LEADER\nKimKyungYoon")));
	//EndingCreditArr.Add(FText::FromString(FString("CHARACTER TEAM\nKimJongBeom\nParkSungWoo\nParkJiYoon\nLeeTaeHwan")));
	//EndingCreditArr.Add(FText::FromString(FString("MONSTER TEAM\nKimSooWon\nCho\nChoiYeongHwan")));
	//EndingCreditArr.Add(FText::FromString(FString("UI TEAM\nBaeYeonDoo\nJoSunWook")));
	FString credit = "[ TEAM LEADER ]\nKimKyungYoon\n\n[ CHARACTER TEAM ]\nKimJongBeom\nParkSungWoo\nParkJiYoon\nLeeTaeHwan\n\n[ MONSTER TEAM ]\nKimSooWon\nChoJeongWoo\nChoiYeongHwan\n\n[ UI TEAM ]\nBaeYeonDoo\nJoSunWook";
	//FString credit = "TEAM LEADER\n±Ë∞Ê¿±\n\nCHARACTER TEAM\nKimJongBeom\nParkSungWoo\nParkJiYoon\nLeeTaeHwan\n\nMONSTER TEAM\nKimSooWon\nChoJeongWoo\nChoiYeongHwan\n\nUI TEAM\nBaeYeonDoo\nJoSunWook";

	EndingCreditText = FText::FromString(credit);
}

void UEndingMessageUserWidget::AddEndingCredit(FText _Text)
{
	EndingCreditArr.Add(_Text);
}
