// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSprite.h"
#include "Global/ContentsLog.h"

UTestMinimapIconComponent::UTestMinimapIconComponent()
{
	if (true == ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Resources/TestLevel/UI/Sprite/PlayerIconSprite.PlayerIconSprite")).Succeeded())
	{
		SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Resources/TestLevel/UI/Sprite/PlayerIconSprite.PlayerIconSprite")).Object);
	}
	else
	{
		LOG(UILog, Fatal, TEXT("UTestMinimapIconComponent::UTestMinimapIconComponent() > ConstructorHelpers::FObjectFinder<UPaperSprite> Error"));
	}

	SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	SetRelativeScale3D(FVector(4.f, 4.f, 4.f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(90.f, 0.f, 90.f));
	SetRelativeRotation(Q);
}

void UTestMinimapIconComponent::BeginPlay()
{
	Super::BeginPlay();
}