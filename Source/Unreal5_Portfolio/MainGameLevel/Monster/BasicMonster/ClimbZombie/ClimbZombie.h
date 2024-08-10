// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "ClimbZombie.generated.h"

class UClimbZombieData;
class UMotionWarpingComponent;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AClimbZombie : public ABasicMonsterBase
{
	GENERATED_BODY()
	
public:
	AClimbZombie();

public:
	UClimbZombieData* GetSettingData() const
	{
		return ClimbZombieSettingData;
	}

	UMotionWarpingComponent* GetMotionWarpingComponent() const
	{
		return MotionWarpingComponent;
	}

protected:
	virtual void InitData(const FMonsterDataRow* BaseData) override;

private:
	UPROPERTY()
	UClimbZombieData* ClimbZombieSettingData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionWarpingComponent* MotionWarpingComponent = nullptr;

};
