// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WidgetDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	FORCEINLINE TSubclassOf<UUserWidget> GetWidget() const
	{
		return Widget;
	}

	FORCEINLINE bool GetStartOn() const
	{
		return StartOn;
	}

protected:

private:
	/// <summary>
	/// UserWidget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<UUserWidget> Widget = TSubclassOf<UUserWidget>();

	/// <summary>
	/// 시작할 때 On, Off상태 (True : 켜고 시작, False : 끄고 시작)
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	bool StartOn = true;
};
