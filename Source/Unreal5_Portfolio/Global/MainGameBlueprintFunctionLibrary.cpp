// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameState.h"
#include "Global/GlobalHUD.h"
#include "Global/ContentsLog.h"

UMainGameInstance* UMainGameBlueprintFunctionLibrary::GetMainGameInstance(const UWorld* WorldContextObject)
{
	UMainGameInstance* MainGameInst = WorldContextObject->GetGameInstanceChecked<UMainGameInstance>();

	if (false == MainGameInst->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (false == Inst->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return MainGameInst;
}

AMainGameState* UMainGameBlueprintFunctionLibrary::GetMainGameState(const UObject* WorldContextObject)
{
	if (nullptr == WorldContextObject)
	{
		return nullptr;
	}

	const UWorld* World = Cast<UWorld>(WorldContextObject);
	AMainGameState* GameState = World->GetGameState<AMainGameState>();
	return GameState;
}

void UMainGameBlueprintFunctionLibrary::PushActor(uint8 _GroupIndex, AActor* _Actor)
{
	if (nullptr == _Actor->GetWorld())
	{
		return;
	}

	const UWorld* World = Cast<UWorld>(_Actor->GetWorld());

	AMainGameState* GameState = World->GetGameState<AMainGameState>();
	if (nullptr == GameState)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == State)"), __FUNCTION__, __LINE__);
	}

	GameState->PushActor(_GroupIndex, _Actor);
}


void UMainGameBlueprintFunctionLibrary::DebugTextPrint(UWorld* _World, FString _Text)
{
#if WITH_EDITOR
	APlayerController* Controller = UGameplayStatics::GetPlayerController(_World, 0);

	if (nullptr == Controller)
	{
		UE_LOG(PlayerLog, Warning, TEXT("%s(%u)> if(nullptr == Controller)"), __FUNCTION__, __LINE__);
		return;
	}

	AGlobalHUD* GlobalHUD = Cast<AGlobalHUD>(Controller->GetHUD());

	GlobalHUD->AddDebugString(_Text);
#endif
}