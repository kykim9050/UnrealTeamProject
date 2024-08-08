// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/MainGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Global/MainGameInstance.h"

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	AllUISetting();
}

void AMainGameHUD::AllUISetting()
{
	Super::AllUISetting();

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

void AMainGameHUD::AllUIOn()
{
	// 인게임에서 디폴트로 켜놓는 애들만 다시 켜주도록 override
	UIOn(EUserWidgetType::HpBar);
	UIOn(EUserWidgetType::Timer);
	UIOn(EUserWidgetType::WeaponSlot);
	UIOn(EUserWidgetType::MiniMap);
	UIOn(EUserWidgetType::Crosshair);
	UIOn(EUserWidgetType::KeyHelp);
	UIOn(EUserWidgetType::Quest);
}
