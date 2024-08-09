// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "TestLevel/Character/TestCharacter.h"

#include "Global/ContentsLog.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "PaperSprite.h"

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

	SetRelativeLocation(FVector(0.f, 0.f, 2000.f));
	SetRelativeScale3D(FVector(6.f, 1.f, 6.f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(90.f, 0.f, 90.f));
	SetRelativeRotation(Q);

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UTestMinimapIconComponent::BeginPlay()
{
	Super::BeginPlay();

	//ATestCharacter* aaa = Cast<ATestCharacter>(GetOwner());
	if (Cast<ATestCharacter>(GetOwner()) == Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		SetSpriteColor(FLinearColor::Red);
	}
}