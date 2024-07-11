// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalHUD.h"
#include "Global/MainGameInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/Debug/TextDebugWidget.h"

void AGlobalHUD::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	TSubclassOf<UUserWidget> Item(Inst->GetGlobalObjectClass("TextDebugWidget"));
	DebugWidgetClass = Item;

	if (nullptr != DebugWidgetClass)
	{
		TextDebugWidget = CreateWidget<UTextDebugWidget>(GetWorld(), DebugWidgetClass);
		TextDebugWidget->AddToViewport();
	}

#endif
}

#if WITH_EDITOR
void AGlobalHUD::AddDebugString(FString _Text)
{
	if (nullptr == TextDebugWidget)
	{
		return;
	}

	TextDebugWidget->AddDebugString(_Text);
}
#endif