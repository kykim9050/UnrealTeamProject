// Fill out your copyright notice in the Description page of Project Settings.


#include "DataEditor.h"
#include "Components/DetailsView.h"
#include "Unreal5_PortfolioEditor.h"
#include "../Unreal5_Portfolio/Global/MainGameBlueprintFunctionLibrary.h"

UDataEditor::UDataEditor()
{

}

void UDataEditor::NativeConstruct()
{
	Super::NativeConstruct();

	DetailView = Cast<UDetailsView>(GetWidgetFromName(TEXT("DataView")));

	if (nullptr == DetailView)
	{
		UE_LOG(EditorLog, Fatal, TEXT("%s(%u) if (nullptr == DetailView)"), __FUNCTION__, __LINE__);
		return;
	}

	//TArray<FString> FileList = TArray<FString>();

	//FString Path = FPaths::ProjectContentDir();
	//FString DataTablePath = "Resources/Global/DataTable";
	//Path = Path + DataTablePath + TEXT("/*.*");

	//IFileManager::Get().FindFiles(FileList, *Path, true, false);

	//UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	//if (nullptr == Inst)
	//{
	//	UE_LOG(EditorLog, Fatal, TEXT("%s(%u)> if (nullptr == DebugText)"), __FUNCTION__, __LINE__);
	//	return;
	//}

	//for (size_t i = 0; i < FileList.Num(); i++)
	//{
	//	// "/Script / Engine.DataTable'/Game/Resources/Global/DataTable/" + 

	//	//TSubclassOf<UDataTable> DataTable =
	//	//	DataTables.Add(DataTable);
	//}

	FString ItemStr = "DataTables";
	FName ItemName = FName(ItemStr);
	DetailView->PropertiesToShow.Add(ItemName);
	DetailView->Modify();
}