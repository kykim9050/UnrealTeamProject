// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "BasicMutant.generated.h"

class UBasicMutantData;
class UMotionWarpingComponent;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMutant : public ABasicMonsterBase
{
	GENERATED_BODY()

public:
	ABasicMutant();

public:
	UBasicMutantData* GetSettingData() const
	{
		return MutantSettingData;
	}
	
	UMotionWarpingComponent* GetMotionWarpingComponent() const
	{
		return MotionWarpingComponent;
	}

protected:
	virtual void InitData(const FMonsterDataRow* BaseData) override;

private:
	UPROPERTY()
	UBasicMutantData* MutantSettingData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionWarpingComponent* MotionWarpingComponent = nullptr;

};
