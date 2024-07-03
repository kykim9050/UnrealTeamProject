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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EMonsterSpawnerType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int MinSpawnNum;

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
	TArray<FMonsterSpawnerInfo> GetSpawnInfo() const
	{
		return SpawnInfo;
	}

private:
	/// <summary>
	/// 몬스터 Spawn 정보
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TArray<FMonsterSpawnerInfo> SpawnInfo;

};

UCLASS()
class UMonsterSpawnerData : public UObject
{
	GENERATED_BODY()

public:
	EMonsterSpawnerType Type = EMonsterSpawnerType::Max;
	int MinSize = -1;
	int MaxSize = -1;

};