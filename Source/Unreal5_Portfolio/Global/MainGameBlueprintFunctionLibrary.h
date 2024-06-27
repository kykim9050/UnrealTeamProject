// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MainGameState.h"
#include "MainGameInstance.h"
#include "MainGameBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMainGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UMainGameInstance* GetMainGameInstance(const UWorld* WorldContextObject);

	static AMainGameState* GetMainGameState(const UObject* WorldContextObject);

	template<typename EnumType>
	static void PushActor(const UObject* WorldContextObject, EnumType _GroupIndex, AActor* _Actor)
	{
		if (nullptr == WorldContextObject)
		{
			return;
		}

		PushActor(WorldContextObject, static_cast<uint8>(_GroupIndex), _Actor);
	}

	// MainGameState 의 AllActor 에 추가
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void PushActor(const UObject* WorldContextObject, uint8 _GroupIndex, AActor* _Actor);

};
