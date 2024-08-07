// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"
#include "MainGameLevel/Player/MainCharacter.h"
#include "MainGameLevel/Object/TriggerBox/TriggerBoxBase.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "MainGameLevel/Player/PlayerItemInformation.h"

// 추후 삭제 필요
#include "TestLevel/Character/TestCharacter.h"

void AMainGameState::SetCurStage_Implementation(EGameStage _Stage)
{
	EGameStage PrevStage = CurStage;

	CurStage = _Stage;

	if (EGameStage::MissionClear == CurStage
	/*	&& EGameStage::Defensing == PrevStage*/)
	{
		SpawnTriggerBox(EndingTriggerBoxPos, EndingTriggerBoxRot);
	}
}

int AMainGameState::GetQuestItemsNum()
{
	int Cnt = 0;

	for (int i = 0; i < static_cast<int>(EQuestItem::Max); i++)
	{
		if (true == QuestItems[i])
		{
			++Cnt;
		}
	}

	return Cnt;
}

AMainGameState::AMainGameState()
{
	int QuestItemsNum = static_cast<int>(EQuestItem::Max);

	for (int i = 0; i < QuestItemsNum; i++)
	{
		QuestItems.Add(false);
	}
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

	GameStateConditionUpdate(_OtherActor, true);

	// 플레이어 수가 일정 수 도달했을 때 조건 체크 함수
	if (MaxPlayerCount == PlayerCount)
	{
		switch (CurStage)
		{
		case EGameStage::Init:
		{
			if (MaxPlayerCount == ItemCount)
			{
				CurStage = EGameStage::VisitArmory;
				PlayerCount = 0;
				ItemCount = 0;
				SetIsStageChange(true);
				break;
			}
			break;
		}
		case EGameStage::VisitArmory:
		{
			if (MaxPlayerCount == ItemCount
				&& MaxBombCount == BombCount)
			{
				CurStage = EGameStage::ObtainFirstSample;
				PlayerCount = 0;
				BombCount = 0;
				ItemCount = 0;
				SetIsStageChange(true);
				break;
			}
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
			break;
		default:
			break;
		}
	}
}

void AMainGameState::GameStateModify_Implementation(AActor* _OtherActor)
{
	if (false == HasAuthority())
	{
		return;
	}

	GameStateConditionUpdate(_OtherActor, false);
}

void AMainGameState::GameStateConditionUpdate(AActor* _OtherActor, bool _IsAdd)
{
	// 추후 MainCharacter로 변경 필요
	ATestCharacter* Player = Cast<ATestCharacter>(_OtherActor);
	//AMainCharacter* Player = Cast<AMainCharacter>(_OtherActor);

	if (nullptr == Player)
	{
		return;
	}

	switch (CurStage)
	{
	case EGameStage::Init:
	{
		if (true == Player->GetItemSlot()[static_cast<int>(EItemType::Melee)].IsItemIn)
		{
			if (true == _IsAdd)
			{
				++ItemCount;
			}
			else
			{
				--ItemCount;
			}
		}
		break;
	}
	case EGameStage::VisitArmory:
	{
		if (true == Player->GetItemSlot()[static_cast<int>(EItemType::Rifle)].IsItemIn)
		{
			if (true == _IsAdd)
			{
				++ItemCount;
			}
			else
			{
				--ItemCount;
			}
		}

		if (true == Player->GetItemSlot()[static_cast<int>(EItemType::Bomb)].IsItemIn)
		{
			if (true == _IsAdd)
			{
				++BombCount;
			}
			else
			{
				--BombCount;
			}
		}
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
		break;
	case EGameStage::Defensing:
		break;
	case EGameStage::MissionClear:
		break;
	default:
		break;
	}
}

void AMainGameState::SpawnTriggerBox(FVector _Pos, FRotator _Rot)
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	TSubclassOf<UObject> TriggerInfo(Inst->GetGlobalObjectClass("StageEndTriggerBox"));

	if (nullptr != TriggerInfo)
	{
		ATriggerBoxBase* EndTriggerBox = GetWorld()->SpawnActor<ATriggerBoxBase>(TriggerInfo, _Pos, _Rot);
	}
}