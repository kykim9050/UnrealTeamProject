// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestPlayHUD.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Global/DataTable/WidgetDataRow.h"

void ATestPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	TMap<FString, FWidgetDataRow>& AllUI = Inst->GetInGameWidgets();
	UEnum* Enum = StaticEnum<EInGameUIType>();

	for (TPair<FString, FWidgetDataRow> Pair : AllUI)
	{
		FWidgetDataRow& Data = Pair.Value;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Data.GetWidget());
		Widget->AddToViewport();

		EInGameUIType Type = static_cast<EInGameUIType>(Enum->GetValueByName(*Pair.Key));

		AllTestPlayWidgets.Add(Type, Widget);

		if (true == Data.GetStartOn())
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}
		else if (false == Data.GetStartOn())
		{
			Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

TMap<EInGameUIType, UUserWidget*> ATestPlayHUD::GetAllTestPlayWidgets()
{
	return AllTestPlayWidgets;
}

UUserWidget* ATestPlayHUD::GetWidget(EInGameUIType _Type)
{
	return AllTestPlayWidgets[_Type];
}

void ATestPlayHUD::UIOn(EInGameUIType _Type)
{
	AllTestPlayWidgets[_Type]->SetVisibility(ESlateVisibility::Visible);
}

void ATestPlayHUD::UIOff(EInGameUIType _Type)
{
	AllTestPlayWidgets[_Type]->SetVisibility(ESlateVisibility::Collapsed);
}

void ATestPlayHUD::UISwitch(EInGameUIType _Type)
{
	UUserWidget** WidgetPtr = AllTestPlayWidgets.Find(_Type);
	UUserWidget* Widget = *WidgetPtr;

	if (ESlateVisibility::Visible == Widget->GetVisibility())
	{
		UIOff(_Type);
	}
	else if (ESlateVisibility::Collapsed == Widget->GetVisibility())
	{
		UIOn(_Type);
	}
}
