// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BossDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBossDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FORCEINLINE FString GetName() const
	{
		return Name;
	}

	FORCEINLINE float GetWalkSpeed() const
	{
		return WalkSpeed;
	}

	FORCEINLINE float GetRunSpeed() const
	{
		return RunSpeed;
	}

protected:

private:
	/// <summary>
	/// Boss 이름
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString Name = "None";

	/// <summary>
	/// 보스 걷기 Speed
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float WalkSpeed = 0.0f;

	/// <summary>
	/// 보스 달리기 Speed
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 0.0f;
};

UCLASS()
class UBossData : public UObject
{
	GENERATED_BODY()

public:
	const FBossDataRow* Data = nullptr;

protected:

private:

};