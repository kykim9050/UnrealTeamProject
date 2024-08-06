// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "BasicZombie.generated.h"

class UBasicZombieData;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicZombie : public ABasicMonsterBase
{
	GENERATED_BODY()

protected:
	virtual void InitData(const FMonsterDataRow* BaseData) override;
	
public:
	UBasicZombieData* GetSettingData() const
	{
		return ZombieSettingData;
	}

protected:
	UPROPERTY()
	UBasicZombieData* ZombieSettingData = nullptr;

};
