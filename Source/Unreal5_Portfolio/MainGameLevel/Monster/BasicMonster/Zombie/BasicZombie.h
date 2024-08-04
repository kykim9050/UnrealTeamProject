// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/BasicMonster/Zombie/BasicZombieData.h"
#include "BasicZombie.generated.h"

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

private:
	UPROPERTY()
	UBasicZombieData* ZombieSettingData = nullptr;

};
