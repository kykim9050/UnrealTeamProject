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

	TMap<EBasicMonsterAnim, FAnimMontageGroup> GetAllAnimMontage() const
	{
		return AllAnimMontages;
	}


	// Test
	ETestMonsterType GetMonsterType() const
	{
		return MonsterType;
	}

	TMap<ETestMonsterAnim, FAnimMontageGroup> GetTestAnimMontage() const
	{
		return TestAnimMontages;
	}

private:
	// 몬스터 UClass
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TSubclassOf<AActor> MonsterUClass = TSubclassOf<AActor>();

	// 걷기 속도
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float WalkSpeed = 300.0f;

	// 달리기 속도
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 600.0f;

	// 몽타주
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TMap<EBasicMonsterAnim, FAnimMontageGroup> AllAnimMontages;
	
	// Test
	// 몬스터 타입
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	ETestMonsterType MonsterType = ETestMonsterType::Noraml;

	// 몽타주
	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TMap<ETestMonsterAnim, FAnimMontageGroup> TestAnimMontages;

};

UCLASS()
class UTestMonsterData : public UObject
{
	GENERATED_BODY()

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// 기본 설정 Data
	const FMonsterDataRow* BaseData;

	// 개별 Data

	// Basic
	UPROPERTY(Replicated)
	float Hp = 100.0f;
	
	float AttackDamage = 0.0f;
	float AttackBoundary = 200.0f;



	/// <summary>
	/// /////
	/// </summary>
	FVector OriginPos = FVector::ZeroVector;


	FVector LerpPos = FVector::ZeroVector;

	float IdleTime = 0.0f;
	
	float Max_PatrolRange = 800.0f;
	
	float AttackTime = 0.0f;

	float ClimbTime = 0.0f;
	float ClimbTotal = 0.0f;

	FVector DestLoc = FVector::ZeroVector;
	float ClimbEndUpTime = 0.0f;

	float AnimationTime = 0.0f;
	float JumpSpeed = 30.0f;
	float JumpAttackDamage = 50.0f;
	float JumpAttackBoundary = 500.0f;

	bool IsChange = false;

	FRotator DestRotate = FRotator::ZeroRotator;
	FRotator MyRotate = FRotator::ZeroRotator;
};
