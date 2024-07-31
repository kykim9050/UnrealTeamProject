// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

// 추후 바꿔야할 헤더 MainCharacter로 변경해야 함
#include "TestLevel/Character/TestCharacter.h"



AMainGameState::AMainGameState()
{

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

	// 추후 MainCharacter로 변경 필요
	ATestCharacter* Player = Cast<ATestCharacter>(_OtherActor);

	if (nullptr == Player)
	{
		LOG(GlobalLog, Fatal, "if (nullptr == Player)");
		return;
	}

	// 조건 관련 변수 정보 갱신
	switch (CurStage)
	{
	case EGameStage::Init:
	{
		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Melee)])
		{
			++ItemCount;
		}
		break;
	}
	case EGameStage::VisitArmory:
	{
		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Rifle1)])
		{
			++ItemCount;
		}

		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Bomb)])
		{
			++BombCount;
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
}

void AMainGameState::GameStateModify_Implementation(AActor* _OtherActor)
{
	if (false == HasAuthority())
	{
		return;
	}

	// 추후 MainCharacter로 변경 필요
	ATestCharacter* Player = Cast<ATestCharacter>(_OtherActor);

	if (nullptr == Player)
	{
		LOG(GlobalLog, Fatal, "if (nullptr == Player)");
		return;
	}

	switch (CurStage)
	{
	case EGameStage::Init:
	{
		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Melee)])
		{
			--ItemCount;
		}
		break;
	}
	case EGameStage::VisitArmory:
	{
		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Rifle1)])
		{
			--ItemCount;
		}

		if (true == Player->IsItemIn[static_cast<int>(EPlayerPosture::Bomb)])
		{
			--BombCount;
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