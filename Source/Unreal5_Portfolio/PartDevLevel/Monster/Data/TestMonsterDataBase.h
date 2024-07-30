// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestMonsterDataBase.generated.h"

struct FMonsterDataRow;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTestMonsterDataBase : public UObject
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
	float AttackRange = 200.0f;

	FVector OriginPos = FVector::ZeroVector;


	/// <summary>
	/// /////
	/// </summary>
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
