// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/TriggerBox/TriggerBoxBase.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"


#include "Global/ContentsLog.h"

ATriggerBoxBase::ATriggerBoxBase()
{
	// 트리거 박스 컴포넌트 초기화
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxBase::OnOverlapBegin);

	// 네트워크 설정
	//bReplicates = true;
	//bAlwaysRelevant = true;
}

void ATriggerBoxBase::BeginPlay()
{
	Super::BeginPlay();

	CenterLocation = GetActorLocation();
}

void ATriggerBoxBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATriggerBoxBase, CenterLocation);
	DOREPLIFETIME(ATriggerBoxBase, LevelSequenceAsset);
	DOREPLIFETIME(ATriggerBoxBase, IsPlayerTP);
}

void ATriggerBoxBase::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (false == HasAuthority())
	{
		LOG(ObjectLog, Error, "서버가 아닙니다.");
		return;
	}

	if (true == IsPlayerTP)
	{
		return;
	}

	IsPlayerTP = true;
	SetAllPlayersLocation(CenterLocation);

	for (FConstPlayerControllerIterator PlayerIt = GetWorld()->GetPlayerControllerIterator(); PlayerIt; ++PlayerIt)
	{
		if (APlayerController* PlayerController = PlayerIt->Get())
		{
			DisablePlayerInput(PlayerController);
		}
	}

	// 시네마틱 시퀀스 재생
	PlayCinematicSequence();

}

void ATriggerBoxBase::SetAllPlayersLocation_Implementation(const FVector& NewLocation)
{

	const float DistanceFromCenter = 300.0f;

	TArray<FVector> PlayerLocations;
	PlayerLocations.Add(FVector(CenterLocation.X, CenterLocation.Y - (DistanceFromCenter * 2), CenterLocation.Z));
	PlayerLocations.Add(FVector(CenterLocation.X, CenterLocation.Y - DistanceFromCenter, CenterLocation.Z));
	PlayerLocations.Add(FVector(CenterLocation.X, CenterLocation.Y + DistanceFromCenter, CenterLocation.Z));
	PlayerLocations.Add(FVector(CenterLocation.X, CenterLocation.Y + (DistanceFromCenter * 2), CenterLocation.Z));

	// 플레이어 컨트롤러 순회 및 위치 설정
	int32 PlayerIndex = 0;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PlayerController = It->Get())
		{
			if (APawn* PlayerPawn = PlayerController->GetPawn())
			{
				// 플레이어를 박스 주변에 배치
				if (PlayerIndex < PlayerLocations.Num())
				{
					PlayerPawn->SetActorLocation(PlayerLocations[PlayerIndex]);

					// 카메라가 바라볼 방향 설정 (Z축을 0으로 고정)
					FVector CameraDirection = FVector(0.0f, 0.0f, 0.0f); // 원하는 방향 설정
					FRotator LookAtRotation = FRotationMatrix::MakeFromX(CameraDirection).Rotator();

					if (ACharacter* Character = Cast<ACharacter>(PlayerPawn))
					{
						UCameraComponent* CameraComponent = Character->FindComponentByClass<UCameraComponent>();
						if (CameraComponent)
						{
							//CameraComponent->SetWorldRotation(LookAtRotation);
							//PlayerPawn->SetActorRotation(FRotator(0,90,0));
						}
					}

					PlayerIndex++;
				}
			}
		}
	}

	//// 모든 플레이어의 위치를 특정 지점으로 설정
	//for (FConstPlayerControllerIterator PlayerIt = GetWorld()->GetPlayerControllerIterator(); PlayerIt; ++PlayerIt)
	//{
	//	if (APlayerController* PlayerController = PlayerIt->Get())
	//	{
	//		if (APawn* PlayerPawn = PlayerController->GetPawn())
	//		{
	//			PlayerPawn->SetActorLocation(NewLocation);
	//		}
	//	}
	//}
}

void ATriggerBoxBase::PlayCinematicSequence_Implementation()
{
	if (!LevelSequenceAsset)
	{
		LOG(ObjectLog, Error, "시네마틱 설정이 되어있지 않습니다.");
		return;
	}

	// 시네마틱 시퀀스를 재생
	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* OutActor;

	// LevelSequencePlayer 생성
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), LevelSequenceAsset, Settings, OutActor);

	if (SequencePlayer)
	{
		SequencePlayer->Play();

		// 시네마틱 시퀀스가 끝났을 때 호출되는 델리게이트 바인딩
		SequencePlayer->OnFinished.AddDynamic(this, &ATriggerBoxBase::OnSequenceFinished);
	}
}

void ATriggerBoxBase::OnSequenceFinished()
{
	// 모든 플레이어의 입력을 다시 활성화
	for (FConstPlayerControllerIterator PlayerIt = GetWorld()->GetPlayerControllerIterator(); PlayerIt; ++PlayerIt)
	{
		if (APlayerController* PlayerController = PlayerIt->Get())
		{
			EnablePlayerInput(PlayerController);
		}
	}

	Destroy();
}

void ATriggerBoxBase::DisablePlayerInput_Implementation(APlayerController* PlayerController)
{
	if (PlayerController && PlayerController->GetPawn())
	{
		PlayerController->GetPawn()->DisableInput(PlayerController);
		PlayerController->DisableInput(PlayerController);
	}
}

void ATriggerBoxBase::EnablePlayerInput_Implementation(APlayerController* PlayerController)
{
	if (PlayerController && PlayerController->GetPawn())
	{
		PlayerController->GetPawn()->EnableInput(PlayerController);
		PlayerController->EnableInput(PlayerController);
	}
}
