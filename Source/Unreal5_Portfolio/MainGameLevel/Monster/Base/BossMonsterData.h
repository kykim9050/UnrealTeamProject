// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/DataTable/BossMonsterDataRow.h"
#include "BossMonsterData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBossMonsterData : public UObject
{
	GENERATED_BODY()

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// 기본 설정 Data
	const FBossMonsterDataRow* BaseData;

	// 개별 Data
	UPROPERTY(Replicated)
	float Hp = 0.0f;

};
