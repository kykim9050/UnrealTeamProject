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
/// 게임 Stage 관련 Enum
/// </summary>
UENUM(BlueprintType)
enum class EGameStage : uint8
{
	Init,					// 게임 플레이 시작 초기
	VisitArmory,			// 무기고 방문
	ObtainFirstSample,		// 샘플1 아이템 확보
	ObtainSecondSample,		// 샘플2 아이템 확보
	ObtainThirdSample,		// 샘플3 아이템 확보
	PlantingBomb,			// 폭탄 설치
	MoveToGatheringPoint,	// 집결지로 이동
	Defensing,				// 거점 방어
	MissionClear,			// 미션 성공
	Max
};


///// <summary>
///// 1, 2, 3, 4 번에 대한 플레이어 자세.
///// </summary>
//UENUM(BlueprintType)
//enum class EPlayerPosture : uint8
//{
//	Rifle1,			// 주 무기 1		// 해당 무기공격 자세 있음
//	Rifle2,			// 주 무기 2		// 해당 무기공격 자세 있음
//	Melee,			// 근거리 무기	// 해당 무기공격 자세 있음
//	Drink,			// 음료(힐팩)	// 인벤토리에만 존재
//	Bomb,			// 설치형 폭탄	// 인벤토리에만 존재
//	Barehand,		// 맨손			// 해당 무기공격 자세 있음
//	SlotMax
//};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Rifle,
	Melee,
	Drink,
	Bomb,
	None
};

UENUM(BlueprintType)
enum class ECameraShakeState : uint8
{
	Shoot,
	Turnback,
	Stop
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
	Scream,
	Rotate,
	GroundAttack,
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
	Scream,
	Chase,
	Fall,
	Jump,
	Climb,
	ClimbEnd,
	Attack,
	JumpAttack,
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
	LRotate		UMETA(DisplayName = "LeftRotate"),
	RRotate		UMETA(DisplayName = "RightRotate"),
	LAttack		UMETA(DisplayName = "LeftAttack"),
	RAttack		UMETA(DisplayName = "RightAttack"),
};

UENUM(BlueprintType)
enum class EBasicMonsterAnim : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Scream		UMETA(DisplayName = "Scream"),
	Walk		UMETA(DisplayName = "Walk"),
	Run			UMETA(DisplayName = "Run"),
	Attack		UMETA(DisplayName = "Attack"),
	JumpAttack	UMETA(DisplayName = "JumpAttack"),
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
	Walk,
	Chase,
	MeleeAttack,
	RangedAttack,
	Dead
};

UENUM(BlueprintType)
enum class EBossMonsterAnim : uint8
{
	Idle				UMETA(DisplayName = "Idle"),
	WalK				UMETA(DisplayName = "Walk"),
	Run					UMETA(DisplayName = "Run"),
	MeleeAttack			UMETA(DisplayName = "MeleeAttack"),
	RangedAttack		UMETA(DisplayName = "RangedAttack"),
	Dead				UMETA(DisplayName = "Dead")
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
	BossHpbar,
	E_Key,
	Num5_Key,
	Quest,
	Timer,
	SlotEmpty,
	NotAreaComment,
	AnyInteractionComment,
	AlreadyHaveComment,
	KeyHelp,

	// Title
	TitleBackground,
	TitleLogo,
	ServerBtn,
	ConnectBrowser,
	SettingBrowser,

	// Lobby
	LobbyButton,
	CantStart,
};


UENUM(BlueprintType)
enum class EPlayerLowerState : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
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

UENUM(BlueprintType)
enum class EPlayerUpperState : uint8
{
	UArm_Idle,
	Rifle_Idle,
	Melee_Idle,
	
	UArm_Attack,
	Melee_Attack,
	Rifle_Attack,
	
	Drink,
	Bomb,

	MoveForward,
	MoveBack,
	MoveLeft,
	MoveRight,
};

UENUM(BlueprintType)
enum class EPlayerFPSTPSState : uint8
{
	FPS	UMETA(DisplayName = "1인칭"),
	TPS	UMETA(DisplayName = "3인칭"),
};

UCLASS()
class UNREAL5_PORTFOLIO_API UContentsEnum : public UObject
{
	GENERATED_BODY()
	
};
