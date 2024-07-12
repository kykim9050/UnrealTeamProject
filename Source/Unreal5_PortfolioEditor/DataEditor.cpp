// Fill out your copyright notice in the Description page of Project Settings.


#include "DataEditor.h"
#include "Components/DetailsView.h"
#include "Global/ContentsLog.h"

UDataEditor::UDataEditor()
{

}

void UDataEditor::NativeConstruct()
{
	Super::NativeConstruct();

	DetailView = Cast<UDetailsView>(GetWidgetFromName(TEXT("DataView")));

	if (nullptr == DetailView)
	{
		//UE_LOG(UILog, Fatal, TEXT("%s(%u) if (nullptr == DetailView)"), __FUNCTION__, __LINE__);
		UE_LOG(LogType, Fatal, TEXT("%s(%u) if (nullptr == DetailView)"), __FUNCTION__, __LINE__);
		return;
	}

	FString ItemStr = "DataTables";
	FName ItemName = FName(ItemStr);
	DetailView->PropertiesToShow.Add(ItemName);
	DetailView->Modify();

	int a = 0;
}