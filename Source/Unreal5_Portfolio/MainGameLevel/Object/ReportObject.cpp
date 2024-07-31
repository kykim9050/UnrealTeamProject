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

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AReportObject::OnCollisionOverlapBegin);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AReportObject::OnCollisionOverlapEnd);
}

void AReportObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AReportObject::OnCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int a = 0;
}

void AReportObject::OnCollisionOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	int a = 0;
}