// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "BossMonsterDataRow.generated.h"

class UAnimMontage;

USTRUCT()
struct UNREAL5_PORTFOLIO_API FRangedAttackRange
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Min = 0.0f;

	UPROPERTY(EditAnywhere)
	float Max = 0.0f;
};


USTRUCT(BlueprintType)
struct FBossMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	// 보스 이름
	UPROPERTY(EditAnywhere)
	FString BossName;

	// 최대 체력
	UPROPERTY(EditAnywhere)
	float MaxHp = 0.0f;

	// 공격 데미지
	UPROPERTY(EditAnywhere)
	float MeleeAttackDamage = 0.0f;

	// 근접 공격 범위
	UPROPERTY(EditAnywhere)
	float MeleeAttackRange = 0.0f;

	// 원거리 공격 범위 
	UPROPERTY(EditAnywhere)
	FRangedAttackRange RangedAttackRange;

	// 원거리 공격 범위 
	UPROPERTY(EditAnywhere)
	float RangedAttackDamage = 0.0f;

	// 걷기 속도
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 0.0f;

	// 추격 속도
	UPROPERTY(EditAnywhere)
	float ChaseSpeed = 0.0f;

	// 몽타주
	UPROPERTY(EditAnywhere)
	TMap<EBossMonsterAnim, class UAnimMontage*> AnimMontages;
};
