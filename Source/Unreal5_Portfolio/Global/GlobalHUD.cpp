// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalHUD.h"
#include "Global/MainGameInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"

void AGlobalHUD::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	//TSubclassOf<UUserWidget> 

#endif
}

#if WITH_EDITOR
void AGlobalHUD::AddDebugString(FString _Text)
{


}
#endif