// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "MonsterDataRow.generated.h"

USTRUCT()
struct UNREAL5_PORTFOLIO_API FAnimMontageGroup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AnimMontages;

};

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

	TMap<EMonsterAnim, class UAnimMontage*> GetAnimMontage() const
	{
		return AnimMontages;
	}

	TMap<EMonsterAnim, FAnimMontageGroup> GetTestAnimMontage() const
	{
		return TestAnimMontages;
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
	TMap<EMonsterAnim, class UAnimMontage*> AnimMontages;

	UPROPERTY(EditAnywhere, meta = (AllowprivateAccess = "true"))
	TMap<EMonsterAnim, FAnimMontageGroup> TestAnimMontages;

};

UCLASS()
class UMonsterData : public UObject
{
	GENERATED_BODY()

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FVector OriginPos = FVector::ZeroVector;

	UPROPERTY(Replicated)
	float Hp = 100.0f;

	float IdleTime = 0.0f;
	
	float Max_PatrolRange = 800.0f;
	
	float AttackTime = 0.0f;
	float AttackDamage = 0.0f;
	float AttackBoundary = 200.0f;

	float ClimbTime = 0.0f;
	
};
