// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/UI/InGame/MinimapCaptureCamera.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestCharacter.h"

// Sets default values
AMinimapCaptureCamera::AMinimapCaptureCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AMinimapCaptureCamera::BeginPlay()
{
	Super::BeginPlay();

	FVector StartPos = FVector(-7400, 62000, 2000);
	SetActorLocation(StartPos);

	if(nullptr == MyCharacter)
	{
		MyCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
}

// Called every frame
void AMinimapCaptureCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (SceneCameraType)
	{
	case EUserWidgetType::MiniMap:
		FollowCharacter();	// 미니맵 씬카메라일 때만 캐릭터 따라다니는 코드  
		break;
	case EUserWidgetType::WorldMap:
		break;
	default:
		break;
	}
	
}

void AMinimapCaptureCamera::SetCharacter(ATestCharacter* _MyCharacter)
{
	MyCharacter = _MyCharacter;
}

void AMinimapCaptureCamera::FollowCharacter()
{
	MyCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (nullptr == MyCharacter)
	{
		return;
	}

	FVector CharacterPos = MyCharacter->GetActorLocation();
	CharacterPos.Z = 4000.f;
	SetActorLocation(CharacterPos);
}

void AMinimapCaptureCamera::SetSceneCameraType(EUserWidgetType _Type)
{
	SceneCameraType = _Type;
}
