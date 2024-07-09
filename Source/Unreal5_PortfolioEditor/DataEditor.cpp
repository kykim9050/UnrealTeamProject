// Fill out your copyright notice in the Description page of Project Settings.


#include "DataEditor.h"
#include "Components/DetailsView.h"
UDataEditor::UDataEditor()
{

}

void UDataEditor::NativeConstruct()
{
	Super::NativeConstruct();

	FName Name = FName(TEXT("TestDataTable"));

	DataView->PropertiesToShow.Add(Name);
}