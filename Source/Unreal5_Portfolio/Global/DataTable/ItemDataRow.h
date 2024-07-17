// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "ItemDataRow.generated.h"


USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 아이템 타입 반환
	/// </summary>
	/// <returns></returns>
	EPlayerPosture GetType() const
	{
		return Type;
	}

	/// <summary>
	/// 아이템 이름 반환
	/// </summary>
	/// <returns></returns>
	FString GetName() const
	{
		return Name;
	}

	/// <summary>
	/// 아이템 데미지 반환
	/// </summary>
	/// <returns></returns>
	int GetDamage() const
	{
		return Damage;
	}

	/// <summary>
	/// 장전 단위 반환
	/// </summary>
	/// <returns></returns>
	int GetReloadNum() const
	{
		return ReloadNum;
	}

	/// <summary>
	/// 아이템 StaticMesh 참조형 반환
	/// </summary>
	/// <returns></returns>
	class UStaticMesh* GetResMesh() const
	{
		return ResMesh;
	}

	/// <summary>
	/// 아이템의 UClass 반환.
	/// </summary>
	/// <returns></returns>
	TSubclassOf<AActor> GetItemUClass() const
	{
		return ItemUClass;
	}

	/// <summary>
	/// 아이템 static mesh component의 relative location 값 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE FVector GetRelLoc() const
	{
		return RelLoc;
	}

	/// <summary>
	/// 아이템 static mesh component의 relative rotation 값 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE FRotator GetRelRot() const
	{
		return RelRot;
	}

protected:

private:
	/// <summary>
	/// 아이템 종류
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EPlayerPosture Type = EPlayerPosture::Barehand;

	/// <summary>
	/// 아이템 이름
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString Name = "";

	/// <summary>
	/// 데미지 값
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int Damage = 0;

	/// <summary>
	/// 장전 단위
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int ReloadNum = -1;

	/// <summary>
	/// 아이템 StaticMesh 리소스 참조 형
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	class UStaticMesh* ResMesh = nullptr;

	/// <summary>
	/// 아이템의 UClass
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<AActor> ItemUClass = TSubclassOf<AActor>();

	/// <summary>
	/// 아이템 static mesh component의 relative location
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FVector RelLoc = FVector(0.0f, 0.0f, 0.0f);

	/// <summary>
	/// 아이템 static mesh component의 relative rotation
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FRotator RelRot = FRotator(0.0f, 0.0f, 0.0f);
};
