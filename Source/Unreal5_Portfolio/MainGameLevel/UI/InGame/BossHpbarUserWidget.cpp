// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/BossHpbarUserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossHpbarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBossHpbarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

}

void UBossHpbarUserWidget::SetHp(float _CurHp, float _MaxHp)
{
	if (_MaxHp == 0.f)
	{
		HpProgress->SetPercent(0.f);
		return;
	}
	HpProgress->SetPercent(_CurHp / _MaxHp);

	FString text = FString::SanitizeFloat(_CurHp) + FString(" / ") + FString::SanitizeFloat(_MaxHp);
	BossHpText->SetText(FText::FromString(text));
}

void UBossHpbarUserWidget::SetBossName(FText _name)
{
	BossNameBlock->SetText(_name);
}
