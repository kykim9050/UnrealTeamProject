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
	TSubclassOf<AActor> GetMonsterUClass() const
	{
		return MonsterUClass;
	}

	float GetWalkSpeed() const
	{
		return WalkSpeed;
	}

	float GetRunSpeed() const
	{
		return RunSpeed;
	}

	TMap<ETestMonsterAnim, FAnimMontageGroup> GetAllAnimMontage() const
	{
		return AllAnimMontages;
	}
	
	ETestMonsterType GetMonsterType() const
	{
		return MonsterType;
	}

private:
	/// <summary>
	/// 기본 Monster 종류
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TSubclassOf<AActor> MonsterUClass = TSubclassOf<AActor>();

	/// <summary>
	/// 걷기 속도
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float WalkSpeed = 300.0f;

	/// <summary>
	/// 달리기 속도
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 600.0f;

	/// <summary>
	/// 몽타주
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TMap<ETestMonsterAnim, FAnimMontageGroup> AllAnimMontages;
	
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	ETestMonsterType MonsterType;

};

UCLASS()
class UMonsterData : public UObject
{
	GENERATED_BODY()

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// 기본 설정 Data
	const FMonsterDataRow* BaseData;

	// 개별 Data
	FVector OriginPos = FVector::ZeroVector;

	FVector LerpPos = FVector::ZeroVector;

	UPROPERTY(Replicated)
	float Hp = 100.0f;

	float IdleTime = 0.0f;
	
	float Max_PatrolRange = 800.0f;
	
	float AttackTime = 0.0f;
	float AttackDamage = 0.0f;
	float AttackBoundary = 200.0f;

	float ClimbTime = 0.0f;
	float ClimbTotal = 0.0f;

	FVector DestLoc = FVector::ZeroVector;
	float ClimbEndUpTime = 0.0f;

	float AnimationTime = 0.0f;
	float JumpSpeed = 30.0f;
	float JumpAttackDamage = 50.0f;
	float JumpAttackBoundary = 500.0f;

	bool IsChange = false;

};
