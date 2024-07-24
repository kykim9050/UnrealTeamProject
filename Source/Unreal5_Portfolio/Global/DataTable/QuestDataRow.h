// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FQuestDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:

	FORCEINLINE FVector GetQuestLocation() const
	{
		return QuestLocation;
	}

	FORCEINLINE FString GetQuestText() const
	{
		return QuestText;
	}

protected:

private:
	/// <summary>
	/// 퀘스트 위치 값
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	FVector QuestLocation = FVector(0.0f, 0.0f, 0.0f);

	/// <summary>
	/// 퀘스트 내용
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	FString QuestText = "";
};
