// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Base/BossMonsterBase.h"

ABossMonsterBase::ABossMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}

