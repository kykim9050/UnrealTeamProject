// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/MainParentHUD.h"
#include "Blueprint/UserWidget.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/WidgetDataRow.h"
#include "Global/ContentsLog.h"

void AMainParentHUD::BeginPlay()
{
	Super::BeginPlay();

	Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
}

void AMainParentHUD::AllUISetting()
{
	
	//Inst의 Widgets를 받아서 AllUI TMap에 넣어줘야 한다.

	//TMap<FString, FWidgetDataRow>& AllUI = Inst->GetInGameWidgets();
	//UEnum* Enum = StaticEnum<EUserWidgetType>();

	//for (TPair<FString, FWidgetDataRow> Pair : AllUI)
	//{
	//	FWidgetDataRow& Data = Pair.Value;

	//	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Data.GetWidget());
	//	Widget->AddToViewport();

	//	EUserWidgetType Type = static_cast<EUserWidgetType>(Enum->GetValueByName(*Pair.Key));

	//	AllWidgets.Add(Type, Widget);

	//	if (true == Data.GetStartOn())
	//	{
	//		Widget->SetVisibility(ESlateVisibility::Visible);
	//	}
	//	else if (false == Data.GetStartOn())
	//	{
	//		Widget->SetVisibility(ESlateVisibility::Collapsed);
	//	}
	//}
	
	
}

TMap<EUserWidgetType, UUserWidget*> AMainParentHUD::GetAllWidgets()
{
	return AllWidgets;
}

UUserWidget* AMainParentHUD::GetWidget(EUserWidgetType _Type)
{
	if (AllWidgets.Find(_Type) == nullptr)
	{
		LOG(UILog, Fatal, "Widget Not Found");
		return nullptr;
	}
	return AllWidgets[_Type];
}

void AMainParentHUD::UIOn(EUserWidgetType _Type)
{
	if (AllWidgets.Find(_Type) == nullptr)
	{
		LOG(UILog, Fatal, "Widget Not Found");
	}
	AllWidgets[_Type]->SetVisibility(ESlateVisibility::Visible);
}

void AMainParentHUD::UIOff(EUserWidgetType _Type)
{
	if (AllWidgets.Find(_Type) == nullptr)
	{
		LOG(UILog, Fatal, "Widget Not Found");
	}
	AllWidgets[_Type]->SetVisibility(ESlateVisibility::Collapsed);
}

void AMainParentHUD::UISwitch(EUserWidgetType _Type)
{
	if (AllWidgets.Find(_Type) == nullptr)
	{
		LOG(UILog, Fatal, "Widget Not Found");
	}

	UUserWidget** WidgetPtr = AllWidgets.Find(_Type);
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

void AMainParentHUD::AllUIOff()
{
	for (auto ui : AllWidgets)
	{
		ui.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMainParentHUD::AllUIOn()
{
	for (auto ui : AllWidgets)
	{
		ui.Value->SetVisibility(ESlateVisibility::Visible);
	}
}
