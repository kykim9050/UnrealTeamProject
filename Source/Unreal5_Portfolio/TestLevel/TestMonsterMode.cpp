// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestMonsterMode.h"

void ATestMonsterMode::BeginPlay()
{
	Super::BeginPlay();

	UClass* BP_MonsterClass = LoadClass<AActor>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/BluePrint/TestLevel/TestMonster/Monster/BP_Zombie1.BP_Zombie1_C'"));
	FTransform Transform;
	Transform.SetLocation({ 0.0f, 0.0f, 500.0f });
	GetWorld()->SpawnActor<AActor>(BP_MonsterClass, Transform);
}
