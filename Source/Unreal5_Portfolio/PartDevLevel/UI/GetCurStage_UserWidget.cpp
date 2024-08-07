// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/UI/GetCurStage_UserWidget.h"

FName UGetCurStage_UserWidget::EnumToFName(EGameStage EnumValue)
{
    switch (EnumValue)
    {
    case EGameStage::Init:
        return FName("Init");
    case EGameStage::VisitArmory:
        return FName("VisitArmory");
    case EGameStage::ObtainFirstSample:
        return FName("ObtainFirstSample");
    case EGameStage::ObtainSecondSample:
        return FName("ObtainSecondSample");
    case EGameStage::ObtainThirdSample:
        return FName("ObtainThirdSample");
    case EGameStage::PlantingBomb:
        return FName("PlantingBomb");
    case EGameStage::MoveToGatheringPoint:
        return FName("MoveToGatheringPoint");
    case EGameStage::Defensing:
        return FName("Defensing");
    case EGameStage::MissionClear:
        return FName("MissionClear");
    default:
        return FName("Unknown");
    }
}

FName UGetCurStage_UserWidget::WidgetGetCurStage()
{
    AMainGameState* WidgetGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
    EGameStage WidgetCurStage = WidgetGameState->GetCurStage();
    EnumToFName(WidgetCurStage);

    return EnumToFName(WidgetCurStage);
}
