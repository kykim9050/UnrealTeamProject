// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestPlayHUD.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Global/DataTable/WidgetDataRow.h"

void ATestPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	AllUISetting();
}

void ATestPlayHUD::AllUISetting()
{
	TMap<FString, FWidgetDataRow>& AllUI = Inst->GetInGameWidgets();
	UEnum* Enum = StaticEnum<EUserWidgetType>();

	for (TPair<FString, FWidgetDataRow> Pair : AllUI)
	{
		FWidgetDataRow& Data = Pair.Value;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Data.GetWidget());
		Widget->AddToViewport();

		EUserWidgetType Type = static_cast<EUserWidgetType>(Enum->GetValueByName(*Pair.Key));

		AllWidgets.Add(Type, Widget);

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