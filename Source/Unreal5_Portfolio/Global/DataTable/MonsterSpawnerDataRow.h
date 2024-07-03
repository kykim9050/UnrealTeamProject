// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "MonsterSpawnerDataRow.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnerInfo : public FTableRowBase
{
	GENERATED_BODY()

	// 스포너 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EMonsterSpawnerType Type;

	// 스포너 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FVector Location;

	// 스폰 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float Ridus;

	// 최소 스폰 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int MinSpawnNum;

	// 최대 스폰 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int MaxSpawnNum;

};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMonsterSpawnerDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	TArray<FMonsterSpawnerInfo> GetSpawnerInfo() const
	{
		return SpawnerInfo;
	}

private:
	/// <summary>
	/// 몬스터 Spawn 정보
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TArray<FMonsterSpawnerInfo> SpawnerInfo;

};

UCLASS()
class UMonsterSpawnerData : public UObject
{
	GENERATED_BODY()

public:
	EMonsterSpawnerType Type = EMonsterSpawnerType::Max;
	FVector Location = FVector::ZeroVector;
	float Radius = 0.0f;
	int MinSize = -1;
	int MaxSize = -1;

};