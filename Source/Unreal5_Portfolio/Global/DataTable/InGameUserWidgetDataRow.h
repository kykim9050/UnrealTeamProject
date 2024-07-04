// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InGameUserWidgetDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInGameUserWidgetDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	TSubclassOf<UUserWidget> GetWidget() const
	{
		return Widget;
	}

protected:

private:
	/// <summary>
	/// ¿Œ∞‘¿” UserWidget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<UUserWidget> Widget = TSubclassOf<UUserWidget>();

};
