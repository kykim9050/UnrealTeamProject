// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "DataEditor.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIOEDITOR_API UDataEditor : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UDataEditor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UDetailsView* DataView = nullptr;

protected:
	void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* TestDataTable = nullptr;
};
