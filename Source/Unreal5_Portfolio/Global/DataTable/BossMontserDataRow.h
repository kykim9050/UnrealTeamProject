// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/ContentsEnum.h"
#include "BossMontserDataRow.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBossMontserDataRow : public UObject
{
	GENERATED_BODY()
	
public:
	// 공격 데미지
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float MeleeAttackDamage = 20.0f;

	// 근접 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float MeleeAttackRange = 200.0f;

	// 투사체 공격력
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float ProjectileDamage = 10.0f;

	// 원거리 공격 범위
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float RangedAttackRange = 1000.0f;

	// 공격 쿨타임
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float AttackCoolTime = 0.0f;

	// 걷기 속도
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float WalkSpeed = 50.0f;

	// 달리기 속도
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 200.0f;

	// 몽타주
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TMap<EBossMonsterAnim, UAnimMontage*> AnimMontages;

};
