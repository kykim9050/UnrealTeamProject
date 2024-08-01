// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/BasicMonster/Mutant/BasicMutantData.h"
#include "BasicMutant.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMutant : public ABasicMonsterBase
{
	GENERATED_BODY()

public:
	UBasicMutantData* GetSettingData() const
	{
		return MutantSettingData;
	}
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UBasicMutantData* MutantSettingData = nullptr;

};
