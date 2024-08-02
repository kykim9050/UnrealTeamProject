// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameLevel/Object/ReportObject.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Global/ContentsLog.h"
#include "MainGameLevel/Player/MainCharacter.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameState.h"

// 추후 삭제 필요
#include "TestLevel/Character/TestCharacter.h"

AReportObject::AReportObject()
{

}

void AReportObject::BeginPlay()
{
	Super::BeginPlay();

	FName Name = FName(TEXT("Sample"));
	Tags.Add(Name);

	FName MeshColName = FName(TEXT("NoCollision"));
	GetMeshComponent()->SetCollisionProfileName(MeshColName);

	FName MainColName = FName(TEXT("MapItem"));
	GetCollisionComponent()->SetCollisionProfileName(MainColName);

	SetInfo(Name);

	FQuat Quat = FQuat();
	UKismetMathLibrary::Quat_SetFromEuler(Quat, FVector(90.0f, 0.0f, 0.0f));
	SetActorRotation(Quat);
}

void AReportObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AReportObject::InterAction_Implementation()
{
	Super::InterAction();

	if (true == HasAuthority())
	{
		AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
		MainGameState->QuestItemGet();
		int QuestItemNum = MainGameState->GetQuestItemsNum();

		switch (QuestItemNum)
		{
		case 1:
			MainGameState->SetCurStage(EGameStage::ObtainSecondSample);
			break;
		case 2:
			MainGameState->SetCurStage(EGameStage::ObtainThirdSample);
			break;
		case 3:
			MainGameState->SetCurStage(EGameStage::PlantingBomb);
			break;
		default:
			break;
		}
	}

	Destroy();
}