// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestTeamHpBarUserWidget.h"

void UTestTeamHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 나 제외 3인의 체력을 초기화.
}

void UTestTeamHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);
}

//float UTestTeamHpBarUserWidget::HPUpdate()
//{
//	int a = 0;
//}