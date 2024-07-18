// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerItemInformation.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UNREAL5_PORTFOLIO_API FPlayerItemInformation
{
	GENERATED_USTRUCT_BODY()
	
public :
	FPlayerItemInformation();
	~FPlayerItemInformation();

public:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName Name = "";
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadMaxNum = -1;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadLeftNum = -1;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Damage = 0;

	// 스태틱 메시
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* MeshRes = nullptr;

	// 스태틱 메시 컴포넌트 상대적 위치
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector RelLoc = FVector(0.0f, 0.0f, 0.0f);
	// 스태틱 메시 컴포넌트 상대적 회전
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator RelRot = FRotator(0.0f, 0.0f, 0.0f);
};
