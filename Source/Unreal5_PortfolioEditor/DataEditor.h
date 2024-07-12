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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UDetailsView* GetDataView() const
	{
		return DetailView;
	}

protected:
	void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TArray<UDataTable*> DataTables = TArray<UDataTable*>();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	class UDetailsView* DetailView = nullptr;
};
