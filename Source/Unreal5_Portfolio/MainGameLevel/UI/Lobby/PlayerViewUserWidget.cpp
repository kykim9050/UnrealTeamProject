// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/PlayerViewUserWidget.h"

#include "Global/ContentsLog.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

//void UPlayerViewUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
//{
//	Super::NativeTick(_MyGeometry, _InDeltaTime);
//
//
//}

UPlayerViewUserWidget::UPlayerViewUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	FString Path = "";
	{
		Path = TEXT("/Game/Resources/MainGameLevel/UI/lobby/MT_LobbyElySelect.MT_LobbyElySelect");
		ConstructorHelpers::FObjectFinder<UMaterial> Material(*Path);
		if (Material.Object == nullptr)
		{
			LOG(UILog, Error, TEXT("Failed to load material"));
		}
		MT_ElyCapture = Material.Object;
	}

	{
		Path = TEXT("/Game/Resources/MainGameLevel/UI/lobby/MT_LobbyVanguardSelect");
		ConstructorHelpers::FObjectFinder<UMaterial> Material(*Path);
		if (Material.Object == nullptr)
		{
			LOG(UILog, Error, TEXT("Failed to load material"));
		}
		MT_VanguardCapture = Material.Object;
	}

	{
		Path = TEXT("/Game/Resources/MainGameLevel/UI/lobby/MT_LobbyAlienSoldierSelect");
		ConstructorHelpers::FObjectFinder<UMaterial> Material(*Path);
		if (Material.Object == nullptr)
		{
			LOG(UILog, Error, TEXT("Failed to load material"));
		}
		MT_AlienSoldierCapture = Material.Object;
	}

	{
		Path = TEXT("/Game/Resources/MainGameLevel/UI/lobby/MT_LobbyCryptoSelect");
		ConstructorHelpers::FObjectFinder<UMaterial> Material(*Path);
		if (Material.Object == nullptr)
		{
			LOG(UILog, Error, TEXT("Failed to load material"));
		}
		MT_CryptoCapture = Material.Object;
	}
}

void UPlayerViewUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MTCharacterType.Add(TTuple<int, UMaterial*>(0, MT_ElyCapture));
	MTCharacterType.Add(TTuple<int, UMaterial*>(1, MT_VanguardCapture));
	MTCharacterType.Add(TTuple<int, UMaterial*>(2, MT_AlienSoldierCapture));
	MTCharacterType.Add(TTuple<int, UMaterial*>(3, MT_CryptoCapture));

}

void UPlayerViewUserWidget::SetPlayerName(int _Order, FText _Name)
{
	switch (_Order) 
	{
	case 0:
		SetP0Name(_Name);
		break;
	case 1:
		SetP1Name(_Name);
		break;
	case 2:
		SetP2Name(_Name);
		break;
	case 3:
		SetP3Name(_Name);
		break;
	default:
		SetP0Name(_Name);
		break;
	}
}

void UPlayerViewUserWidget::SetPlayerView(int _Order, int _CharacterType)
{
	switch (_Order)
	{
	case 0:
		P0Img->SetBrushFromMaterial(MTCharacterType[_CharacterType]);
		break;
	case 1:
		P1Img->SetBrushFromMaterial(MTCharacterType[_CharacterType]);
		break;
	case 2:
		P2Img->SetBrushFromMaterial(MTCharacterType[_CharacterType]);
		break;
	case 3:
		P3Img->SetBrushFromMaterial(MTCharacterType[_CharacterType]);
		break;
	default:
		P0Img->SetBrushFromMaterial(MTCharacterType[_CharacterType]);
		break;
	}
	
}

void UPlayerViewUserWidget::SetP0Name(FText _Name)
{
	P0Name->SetText(_Name);
}


void UPlayerViewUserWidget::SetP1Name(FText _Name)
{
	P1Name->SetText(_Name);
}

void UPlayerViewUserWidget::SetP2Name(FText _Name)
{
	P2Name->SetText(_Name);
}

void UPlayerViewUserWidget::SetP3Name(FText _Name)
{
	P3Name->SetText(_Name);
}
