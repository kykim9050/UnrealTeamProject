// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/ReportObject.h"

void AReportObject::BeginPlay()
{
	Super::BeginPlay();

	FName Name = FName(TEXT("Sample"));
	Tags.Add(Name);

	SetInfo(Name);
}

void AReportObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}