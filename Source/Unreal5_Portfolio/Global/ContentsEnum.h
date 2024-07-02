// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ContentsEnum.generated.h"


// Contents 전반적으로 사용하는 Enum class
UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Player,
	Monster,
	Max
};

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Walk	UMETA(DisplayName = "Walk"),
	Run		UMETA(DisplayName = "Run"),
	Jump	UMETA(DisplayName = "Jump"),
	Crouch	UMETA(DisplayName = "Crouch"),
	Fire	UMETA(DisplayName = "Fire"),
};

/// <summary>
/// 1, 2, 3, 4 번에 대한 플레이어 자세.
/// </summary>
UENUM(BlueprintType)
enum class EPlayerPosture : uint8
{
	Number0 UMETA(DisplayName = "Barehand"),
	Number1 UMETA(DisplayName = "Rifle"),
	Number2 UMETA(DisplayName = "Pistol"),
	Number3 UMETA(DisplayName = "근거리 무기"),
	Number4 UMETA(DisplayName = "투척 무기"),
	Number5 UMETA(DisplayName = "특수 무기")
};

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Patrol,
	Chase,
	Attack,
	Dead
};

UENUM(BlueprintType)
enum class EMonsterAnim : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Walk	UMETA(DisplayName = "Walk"),
	Run		UMETA(DisplayName = "Run"),
	Attack	UMETA(DisplayName = "Attack"),
	Dead	UMETA(DisplayName = "Dead")
};

UCLASS()
class UNREAL5_PORTFOLIO_API UContentsEnum : public UObject
{
	GENERATED_BODY()
	
};
