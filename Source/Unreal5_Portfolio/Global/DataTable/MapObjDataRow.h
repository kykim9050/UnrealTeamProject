// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapObjDataRow.generated.h"

/**
 * 
 */
USTRUCT()
struct FMapObjDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FORCEINLINE class UStaticMesh* GetMesh() const
	{
		return Mesh;
	}

	FORCEINLINE TSubclassOf<UObject> GetInteractObjClass() const
	{
		return InteractObjClass;
	}

protected:

private:
	/// <summary>
	/// 맵 오브젝트 매쉬
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	class UStaticMesh* Mesh = nullptr;

	/// <summary>
	/// 상호작용할 오브젝트
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<UObject> InteractObjClass = TSubclassOf<UObject>();
};
