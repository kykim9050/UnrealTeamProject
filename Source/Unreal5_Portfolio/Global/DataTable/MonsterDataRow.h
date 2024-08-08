// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "Global/Animation/MainMultiAnimInstance.h"
#include "MonsterDataRow.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	// 걷기 속도
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 300.0f;

	// 달리기 속도
	UPROPERTY(EditAnywhere)
	float RunSpeed = 600.0f;

	// 공격 범위
	UPROPERTY(EditAnywhere)
	float AttackRange = 200.0f;

	// 몽타주
	UPROPERTY(EditAnywhere)
	TMap<EBasicMonsterAnim, FAnimMontageGroup> AllAnimMontages;
};