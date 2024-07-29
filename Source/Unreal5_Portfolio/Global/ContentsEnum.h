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

UENUM(BlueprintType)
enum class EGameStage : uint8
{
	Init					UMETA(DisplayName = "게임 플레이 시작 초기"),
	VisitArmory				UMETA(DisplayName = "무기고 방문"),
	ObtainFirstSample		UMETA(DisplayName = "샘플1 아이템 확보"),
	ObtainSecondSample		UMETA(DisplayName = "샘플2 아이템 확보"),
	ObtainThirdSample		UMETA(DisplayName = "샘플3 아이템 확보"),
	PlantingBomb			UMETA(DisplayName = "폭탄 설치"),
	MoveToGatheringPoint	UMETA(DisplayName = "집결지로 이동"),
	Defensing				UMETA(DisplayName = "거점 방어"),
	MissionClear			UMETA(DisplayName = "미션 성공")
};


/// <summary>
/// 1, 2, 3, 4 번에 대한 플레이어 자세.
/// </summary>
UENUM(BlueprintType)
enum class EPlayerPosture : uint8
{
	Rifle1,			// 주 무기 1		// 해당 무기공격 자세 있음
	Rifle2,			// 주 무기 2		// 해당 무기공격 자세 있음
	Melee,			// 근거리 무기	// 해당 무기공격 자세 있음
	Drink,			// 음료(힐팩)	// 인벤토리에만 존재
	Bomb,			// 설치형 폭탄	// 인벤토리에만 존재
	Barehand,		// 맨손			// 해당 무기공격 자세 있음
	SlotMax
};

UENUM(BlueprintType)
enum class ETestMonsterState : uint8
{
	Idle,
	Patrol,
	Chase,
	Fall,
	Jump,
	Climb,
	ClimbEnd,
	Attack,
	Dead,
	JumpAttack,
	Scream
};

UENUM(BlueprintType)
enum class ETestMonsterType : uint8
{
	Noraml,
	Crawl,
	Boss
};

UENUM(BlueprintType)
enum class EBasicMonsterState : uint8
{
	Idle,
	Patrol,
	Chase,
	Fall,
	Jump,
	Climb,
	ClimbEnd,
	Attack,
	Dead
};

UENUM(BlueprintType)
enum class ETestMonsterAnim : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Walk		UMETA(DisplayName = "Walk"),
	Run			UMETA(DisplayName = "Run"),
	Attack		UMETA(DisplayName = "Attack"),
	Dead		UMETA(DisplayName = "Dead"),
	Climb		UMETA(DisplayName = "Climb"),
	ClimbEnd	UMETA(DisplayName = "ClimbEnd"),
	Scream		UMETA(DisplayName = "Scream"),
	JumpAttack	UMETA(DisplayName = "JumpAttack"),
};

UENUM(BlueprintType)
enum class EBasicMonsterAnim : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Walk		UMETA(DisplayName = "Walk"),
	Run			UMETA(DisplayName = "Run"),
	Attack		UMETA(DisplayName = "Attack"),
	Dead		UMETA(DisplayName = "Dead"),
	Climb		UMETA(DisplayName = "Climb"),
	ClimbEnd	UMETA(DisplayName = "ClimbEnd")
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
enum class EUserWidgetType : uint8
{
	// InGame
	HpBar,
	WeaponSlot,
	MiniMap,
	Leaderboard,
	Crosshair,
	WorldMap,
	ReloadComment,

	// Title
	TitleBackground,
	TitleLogo,
	ServerBtn,
	ConnectBrowser,
	SettingBrowser,
};


UENUM(BlueprintType)
enum class EPlayerLowerState : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Crouch	UMETA(DisplayName = "CrouchIdle"),
};

UENUM(BlueprintType)
enum class EPlayerUpperState : uint8
{
	Barehand_Attack	UMETA(DisplayName = "Barehand_Attack"),		// 맨손 공격
	Rifle_Attack		UMETA(DisplayName = "Rifle_Attack"),	// 주무기 공격
	//Pistol		UMETA(DisplayName = "PistolAttack"),		// 보조무기
	//Melee		UMETA(DisplayName = "MeleeAttack"),				// 근거리무기
	//Throwing	UMETA(DisplayName = "ThrowingAttack"),			// 투척무기
	//Supply		UMETA(DisplayName = "Supplies"),			// 그 외 소모품 아이템
	//SlotMax
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
