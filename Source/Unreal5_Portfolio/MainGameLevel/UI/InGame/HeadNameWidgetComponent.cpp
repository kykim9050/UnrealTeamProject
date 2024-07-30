// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"

#include "Kismet/KismetMathLibrary.h"

UHeadNameWidgetComponent::UHeadNameWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HeadNameWidget(TEXT("/Game/BluePrint/MainGameLevel/UI/InGame/WBP_HeadName"));
	if (true == HeadNameWidget.Succeeded())
	{
		SetWidgetClass(HeadNameWidget.Class);
	}
	else
	{
		int a = 0;
	}

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UHeadNameWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetRelativeLocation(FVector(0, 0, 50));
	SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(0.f, 0.f, 0.f));
	SetRelativeRotation(Q);

	SetWidgetSpace(EWidgetSpace::Screen);
}
