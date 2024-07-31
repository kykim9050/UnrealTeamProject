// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/ReportObject.h"
#include "Components/CapsuleComponent.h"

void AReportObject::BeginPlay()
{
	Super::BeginPlay();

	FName Name = FName(TEXT("Sample"));
	Tags.Add(Name);

	FName MeshColName = FName(TEXT("NoCollision"));
	GetMeshComponent()->SetCollisionProfileName(MeshColName);

	FName MainColName = FName(TEXT("MapItem"));
	GetCollisionComponent()->SetCollisionProfileName(MainColName);

	SetInfo(Name);
	
}

void AReportObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}