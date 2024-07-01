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
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Jump UMETA(DisplayName = "Jump"),
	Crouch UMETA(DisplayName = "Crouch"),
	Fire UMETA(DisplayName = "Fire"),
};

/// <summary>
/// 1, 2, 3, 4 번에 대한 플레이어 자세.
/// </summary>
UENUM(BlueprintType)
enum class EPlayerPosture : uint8
{
	Number1 UMETA(DIsplayName = "주 무기"),
	Number2 UMETA(DIsplayName = "보조 무기"),
	Number3 UMETA(DIsplayName = "근거리 무기"),
	Number4 UMETA(DIsplayName = "투척 무기"),
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
enum class EZombie1Anim : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Dead
};

UCLASS()
class UNREAL5_PORTFOLIO_API UContentsEnum : public UObject
{
	GENERATED_BODY()
	
};
