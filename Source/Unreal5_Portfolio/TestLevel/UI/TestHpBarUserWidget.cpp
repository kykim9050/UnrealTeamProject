// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHpBarUserWidget.h"
#include "DefaultHpBarUserWidget.h"
#include "TestLevel/Character/TestCharacter.h"

void UTestHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetInit();
}

void UTestHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

	ATestCharacter* MyCharacter = Cast<ATestCharacter>(GetOwningPlayerPawn());
	if (-1 == MainPlayerToken && nullptr != MyCharacter)
	{
		MyCharacter->SendTokenToHpBarWidget();
	}

}

void UTestHpBarUserWidget::WidgetInit()
{
	// HpWidgets 세팅
	HpWidgets.Add(MainPlayer);
	HpWidgets.Add(Player2);
	HpWidgets.Add(Player3);
	HpWidgets.Add(Player4);

	// NickName 초기화
	for (int i = 0; i < 4; ++i)
	{
		FString NameInit = "Player" + FString::FromInt(i);
		HpWidgets[i]->SetNickName(FText::FromString(NameInit));
	}

	// HP 초기화
	for (int i = 0; i < 4; ++i)
	{
		HpWidgets[i]->SetHp(1.f);
	}
}

//void UTestHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
//{
//	Super::NativeTick(_MyGeometry, _InDeltaTime);
//
//}

// 이 함수는 메인 플레이어만 실행해야 합니다. (플레이하는 컴퓨터당 1회 실행)
void UTestHpBarUserWidget::HpbarInit_ForMainPlayer(int _MainPlayerToken)
{
	MainPlayerToken = _MainPlayerToken;

	for (int i = 0; i < 4; ++i)
	{
		if (i == MainPlayerToken)
		{
			continue;
		}
		OtherPlayerNum.Add(i);
	}
}

void UTestHpBarUserWidget::HpbarUpdate(int _Token, float _CurHp, float _MaxHp)
{
	if (-1 == MainPlayerToken)
	{
		return;
	}

	// 테스트용
	//if (_Token == 1)
	//{
	//	int a = 0;
	//}
	//else if (_Token == 0)
	//{
	//	int a = 0;
	//	_CurHp = 40.f;
	//}

	//if (MainPlayerIndex == 1)
	//{
	//	int a = 0;
	//}
	//else if (MainPlayerIndex == 0)
	//{
	//	int a = 0;
	//}

	if (MainPlayerToken == _Token)
	{
		HpWidgets[0]->SetHp(_CurHp / _MaxHp);
		return;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (OtherPlayerNum[i] == _Token)
		{
			HpWidgets[i + 1]->SetHp(_CurHp / _MaxHp);
			return;
		}
	}
	
}

void UTestHpBarUserWidget::NickNameUpdate(int _Token, FText _nickname)
{
	if (-1 == MainPlayerToken)
	{
		return;
	}

	if (MainPlayerToken == _Token)
	{
		HpWidgets[0]->SetNickName(_nickname);
		return;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (OtherPlayerNum[i] == _Token)
		{
			HpWidgets[i + 1]->SetNickName(_nickname);
			return;
		}
	}
}


