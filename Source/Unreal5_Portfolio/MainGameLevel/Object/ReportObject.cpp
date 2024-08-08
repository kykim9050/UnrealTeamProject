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
		
		if (nullptr == MainGameState)
		{
			LOG(ObjectLog, Fatal, "if (nullptr == MainGameState)");
			return;
		}

		EGameStage CurStage = MainGameState->GetCurStage();

		switch (CurStage)
		{
		case EGameStage::ObtainFirstSample:
			MainGameState->SetCurStage(EGameStage::ObtainSecondSample);
			break;
		case EGameStage::ObtainSecondSample:
			MainGameState->SetCurStage(EGameStage::ObtainThirdSample);
			break;
		case EGameStage::ObtainThirdSample:
			MainGameState->SetCurStage(EGameStage::PlantingBomb);
			break;
		default:
			break;
		}
	}

	Destroy();
}