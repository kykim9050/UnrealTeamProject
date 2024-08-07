// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BossKrakenProjectileSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL5_PORTFOLIO_API UBossKrakenProjectileSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	UBossKrakenProjectileSpawnPoint();

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FVector> SpawnLocation;
		
};
