// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Global/DataTable/MonsterDataRow.h"

#include "BasicMonsterData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBasicMonsterData : public UObject
{
	GENERATED_BODY()
	
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// 기본 설정 Data
	const FMonsterDataRow* BaseData;

	// 개별 Data
	UPROPERTY(Replicated)
	float Hp = 100.0f;

	// 스폰 위치
	FVector OriginPos = FVector::ZeroVector;
	
	float TimeCount = 0.0f;
	
	// 데이터 테이블 승격 필요
	float PatrolRange = 800.0f;

	float AttackDamage = 34.0f;
	float AttackRange = 200.0f;

	bool bScream = false;
};
