// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/CharacterSelectionUserWidget.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

void UCharacterSelectionUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharTypeName.Add(TTuple<int, FName>(0, FName("TestPlayer")));
	CharTypeName.Add(TTuple<int, FName>(1, FName("Vanguard")));
	CharTypeName.Add(TTuple<int, FName>(2, FName("AlienSoldier")));
	CharTypeName.Add(TTuple<int, FName>(3, FName("Crypto")));
}

void UCharacterSelectionUserWidget::SetSelectedCharacter(int _Num)
{
	// 멤버 변수에 저장
	SelectedCharacter = _Num;

	// MainGameInstance에 저장 
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
	}

	Inst->SetUIToSelectCharacter(CharTypeName[_Num]);
}
