// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestPlayHUD.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"

void ATestPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	TMap<FString, TSubclassOf<UUserWidget>>& AllUI = Inst->GetInGameWidgets();
	UEnum* Enum = StaticEnum<EInGameUIType>();

	for (TPair<FString, TSubclassOf<UUserWidget>> Pair : AllUI)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Pair.Value);
		Widget->AddToViewport();

		EInGameUIType Type = static_cast<EInGameUIType>(Enum->GetValueByName(*Pair.Key));

		AllTestPlayWidgets.Add(Type, Widget);
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