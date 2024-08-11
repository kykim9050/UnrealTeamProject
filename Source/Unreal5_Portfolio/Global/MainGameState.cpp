// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"
#include "MainGameLevel/Player/MainCharacter.h"
#include "MainGameLevel/Object/TriggerBox/TriggerBoxBase.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "MainGameLevel/Player/PlayerItemInformation.h"
#include "Components/AudioComponent.h"
#include "MainGameLevel/Object/TriggerBox/StageCheckBox.h"

// 추후 삭제 필요
#include "TestLevel/Character/TestCharacter.h"

void AMainGameState::SetCurStage_Implementation(EGameStage _Stage)
{
	EGameStage PrevStage = CurStage;

	CurStage = _Stage;

	if (EGameStage::MissionClear == CurStage
		&& EGameStage::Defensing == PrevStage)
	{
		UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		TSubclassOf<UObject> TriggerInfo(Inst->GetGlobalObjectClass("StageEndCheckBox"));

		if (nullptr != TriggerInfo)
		{
			AStageCheckBox* StageCheckBox = GetWorld()->SpawnActor<AStageCheckBox>(TriggerInfo, EndingTriggerBoxPos, EndingTriggerBoxRot);
			StageCheckBox->SetActorScale3D(TriggerBoxColScale);
		}
	}
}


AMainGameState::AMainGameState()
{
	BackgroundSound = CreateDefaultSubobject<UAudioComponent>("BackgroundSound");
	BackgroundSound->SetupAttachment(RootComponent);
	//BackgroundSound->SetIsReplicated(false);
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, CurStage);
}

void AMainGameState::PushActor(uint8 _Index, AActor* _Actor)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	AllActor[_Index]->Actors.Add(_Actor);
}

UActorGroup* AMainGameState::GetActorGroup(uint8 _Index)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	return AllActor[_Index];
}

void AMainGameState::GameStateCheck_Implementation(AActor* _OtherActor)
{
	if (false == HasAuthority())
	{
		return;
	}

	if (false == SetPlayerMaxNum)
	{
		MaxPlayerCount = PlayerArray.Num();
		SetPlayerMaxNum = true;
	}

	// 플레이어 수가 일정 수 도달했을 때 조건 체크 함수
	if (MaxPlayerCount == PlayerCount)
	{
		switch (CurStage)
		{
		case EGameStage::Init:
		{
			CurStage = EGameStage::VisitArmory;
			PlayerCount = 0;
			SetIsStageChange(true);
			break;
		}
		case EGameStage::VisitArmory:
		{
			CurStage = EGameStage::ObtainFirstSample;
			PlayerCount = 0;
			SetIsStageChange(true);
			break;
		}
		case EGameStage::ObtainFirstSample:
			break;
		case EGameStage::ObtainSecondSample:
			break;
		case EGameStage::ObtainThirdSample:
			break;
		case EGameStage::PlantingBomb:
			break;
		case EGameStage::MoveToGatheringPoint:
		{
			CurStage = EGameStage::Defensing;
			PlayerCount = 0;
			SetIsStageChange(true);
			break;
		}
		case EGameStage::Defensing:
			break;
		case EGameStage::MissionClear:
		{
			SpawnTriggerBox(EndingTriggerBoxPos, EndingTriggerBoxRot);
			break;
		}
		default:
			break;
		}
	}
}

void AMainGameState::SetIsPlayCinematic(bool _Value)
{
	bPlayCinematic = _Value;
}

void AMainGameState::SpawnTriggerBox(FVector _Pos, FRotator _Rot)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	TSubclassOf<UObject> TriggerInfo(Inst->GetGlobalObjectClass("StageEndTriggerBox"));

	if (nullptr != TriggerInfo)
	{
		ATriggerBoxBase* EndTriggerBox = GetWorld()->SpawnActor<ATriggerBoxBase>(TriggerInfo, _Pos, _Rot);
		EndTriggerBox->SetActorScale3D(TriggerBoxColScale);
	}
}

void AMainGameState::PlayBackgroundSound()
{
	BackgroundSound->Play();
}

void AMainGameState::StopBackgroundSound()
{
	BackgroundSound->Stop();
}