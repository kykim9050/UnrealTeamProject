// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestPlayHUD.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"

void ATestPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	TMap<FString, TSubclassOf<UUserWidget>>& AllUI = Inst->GetInGameWidgets();

	for (TPair<FString, TSubclassOf<UUserWidget>> Pair : AllUI)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Pair.Value);
		Widget->AddToViewport();
		AllTestPlayWidgets.Add(Pair.Key, Widget);
	}
}