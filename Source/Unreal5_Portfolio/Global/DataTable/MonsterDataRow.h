// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
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

	TMap<EMonsterAnim, class UAnimMontage*> GetAnimMontage() const
	{
		return AnimMontages;
	}

private:
	/// <summary>
	/// 기본 Monster 종류
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<AActor> MonsterUClass = TSubclassOf<AActor>();

	/// <summary>
	/// 걷기 속도
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float WalkSpeed = 300.0f;

	/// <summary>
	/// 달리기 속도
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 600.0f;

	/// <summary>
	/// 몽타주
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TMap<EMonsterAnim, class UAnimMontage*> AnimMontages;
};

UCLASS()
class UMonsterData : public UObject
{
	GENERATED_BODY()

public:
	const FMonsterDataRow* Data;

	FVector OriginPos = FVector::ZeroVector;
	float IdleTime = 0.0f;

	float Max_PatrolRange = 0.0f;
};
