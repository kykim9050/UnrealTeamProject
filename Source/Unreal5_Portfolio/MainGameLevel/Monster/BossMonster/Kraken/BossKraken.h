// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BossMonsterBase.h"
#include "BossKraken.generated.h"

class UBoxComponent;
class UBossKrakenData;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABossKraken : public ABossMonsterBase
{
	GENERATED_BODY()

public:
	ABossKraken();

public:
	UBossKrakenData* GetSettingData() const
	{
		return BossKrakenSettingData;
	}

protected:
	virtual void InitData(const FBossMonsterDataRow* BaseData);
	
private:
	UPROPERTY()
	UBossKrakenData* BossKrakenSettingData = nullptr;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent* BodyComponent = nullptr;

private:
	// Effect
	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* SmashParticle = nullptr;

};
