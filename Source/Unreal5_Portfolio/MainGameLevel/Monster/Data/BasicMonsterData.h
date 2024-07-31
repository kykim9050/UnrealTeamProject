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
	const FMonsterDataRow* GetBaseData() const
	{
		return BaseData;
	}

	float GetHp()
	{
		return Hp;
	}

	FVector GetOriginPos()
	{
		return OriginPos;
	}

	float GetPatrolRange()
	{
		return PatrolRange;
	}

	float GetAttackDamage()
	{
		return AttackDamage;
	}

	float GetAttackRange()
	{
		return AttackRange;
	}

public:
	void SetBaseData(const FMonsterDataRow* Value)
	{
		BaseData = Value;
	}

	void SetHp(float Value)
	{
		Hp = Value;
	}

	void SetOriginPos(const FVector& Value)
	{
		OriginPos = Value;
	}

private:
	// 기본 설정 Data
	const FMonsterDataRow* BaseData;

	// 개별 Data
	UPROPERTY(Replicated)
	float Hp = 100.0f;

	// 스폰 위치
	FVector OriginPos = FVector::ZeroVector;

	float PatrolRange = 800.0f;

	float AttackDamage = 34.0f;
	float AttackRange = 200.0f;

public:
	float TimeCount = 0.0f;

};
