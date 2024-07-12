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
	Rifle		UMETA(DisplayName = "RifleAttack"),		// 주무기
	Pistol		UMETA(DisplayName = "PistolAttack"),	// 보조무기
	Melee		UMETA(DisplayName = "MeleeAttack"),		// 근거리무기
	Throwing	UMETA(DisplayName = "ThrowingAttack"),	// 투척무기
	Supply		UMETA(DisplayName = "Supplies"),		// 그 외 소모품 아이템
	Barehand	UMETA(DisplayName = "BarehandAttack"),	// 맨손공격
	SlotMax
};

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Patrol,
	Chase,
	Fall,
	Jump,
	Climb,
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

UENUM()
enum class EMonsterSpawnerType : uint8
{
	Once,
	Continuous,
	Max
};

UENUM(BlueprintType)
enum class EBossMonsterState : uint8
{
	Idle,
	Chase,
	MeleeAttack,
	RangedAttack,
	Dead
};

UENUM(BlueprintType)
enum class EBossMonsterAnim : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	WalK	UMETA(DisplayName = "Walk"),
	Run	UMETA(DisplayName = "Run"),
	MeleeAttack	UMETA(DisplayName = "MeleeAttack"),
	RangedAttack	UMETA(DisplayName = "RangedAttack"),
	Dead	UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EInGameUIType : uint8
{
	HpBar,
	WeaponSlot,
	MiniMap,
	Leaderboard,
	Crosshair,
};


UENUM(BlueprintType)
enum class EPlayerLowerState : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Jump	UMETA(DisplayName = "Jump"),
	Crouch	UMETA(DisplayName = "CrouchIdle"),
};

UENUM(BlueprintType)
enum class EPlayerMoveDir : uint8
{
	Forward	UMETA(DisplayName = "Forward"),
	Back	UMETA(DisplayName = "Back"),
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
};

UCLASS()
class UNREAL5_PORTFOLIO_API UContentsEnum : public UObject
{
	GENERATED_BODY()
	
};
