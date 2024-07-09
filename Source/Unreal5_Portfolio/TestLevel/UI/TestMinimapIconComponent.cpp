// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestMinimapIconComponent.h"
#include "Kismet/KismetMathLibrary.h"

UTestMinimapIconComponent::UTestMinimapIconComponent()
{
	SetRelativeLocation(FVector(0.f, 0.f, 1000.f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(0.f, -90.f, 0.f));
	SetRelativeRotation(Q);
}

void UTestMinimapIconComponent::BeginPlay()
{

}