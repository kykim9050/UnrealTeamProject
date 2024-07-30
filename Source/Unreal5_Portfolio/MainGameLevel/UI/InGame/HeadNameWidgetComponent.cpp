// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	SetRelativeLocation(FVector(0, 0, 75));
	SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(0.f, 0.f, 0.f));
	SetRelativeRotation(Q);
}

void UHeadNameWidgetComponent::BilboardRotate(FVector _WorldLocation)
{
	FVector CameraLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(_WorldLocation, CameraLoc);
	FVector X = FVector::ZeroVector;
	FVector Y = FVector::ZeroVector;
	FVector Z = FVector::ZeroVector;
	UKismetMathLibrary::GetAxes(Rot, X, Y, Z);
	FRotator Res = UKismetMathLibrary::Conv_VectorToRotator(X);
	Res = FRotator(0.0f, Res.Yaw, 0.0f);
	SetWorldRotation(Res);
}
