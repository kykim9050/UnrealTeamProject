// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Global/ContentsEnum.h"
#include "MainGameState.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API UActorGroup : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> Actors;
};

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainGameState : public AGameState
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void PushActor(EnumType _Index, AActor* _Actor)
	{
		PushActor(static_cast<uint8>(_Index), _Actor);
	}

	void PushActor(uint8 _Index, AActor* _Actor);

	template<typename EnumType>
	UActorGroup* GetActorGroup(EnumType _Index)
	{
		return GetActorGroup(static_cast<uint8>(_Index));
	}

	UActorGroup* GetActorGroup(uint8 _Index);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EGameStage GetCurStage() const
	{
		return CurStage;
	}

	UFUNCTION()
	FORCEINLINE void SetCurStage(EGameStage _Stage)
	{
		CurStage = _Stage;
	}

	/// <summary>
	/// Melee 확보시 호출되는 함수
	/// </summary>
	UFUNCTION(Reliable, NetMulticast)
	void AddMeleeNum();
	void AddMeleeNum_Implementation();

	/// <summary>
	/// 확보된 Melee 수를 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE int GetMeleeNum() const
	{
		return MeleeNum;
	}

	/// <summary>
	/// 무기고에서 아이템 확보시 아이템 수를 갱신하는 함수
	/// </summary>
	void AddArmoryWeaponNum(EPlayerPosture _ItemType);

	/// <summary>
	/// 확보된 Rifle 수를 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE int GetRifleNum() const
	{
		return RifleNum;
	}

	/// <summary>
	/// 확보된 Bomb 수를 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE int GetBombNum() const
	{
		return BombNum;
	}

	/// <summary>
	/// 보스1 스테이지 클리어
	/// </summary>
	void SetClearBoss1Stage();
	
	/// <summary>
	/// 보스2 스테이지 클리어
	/// </summary>
	void SetClearBoss2Stage();

protected:
	AMainGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, UActorGroup*> AllActor;
	
	/// <summary>
	/// 현재 게임 Stage 상태(단계)
	/// </summary>
	UPROPERTY(Replicated)
	EGameStage CurStage = EGameStage::Init;

	/// <summary>
	/// 현재 확보한 Melee 수
	/// </summary>
	UPROPERTY(Replicated)
	int MeleeNum = 0;

	/// <summary>
	/// 확보 가능한 최대 Melee 수
	/// </summary>
	UPROPERTY()
	int MaxMeleeNum = 4;

	/// <summary>
	/// 현재 확보한 Rifle 수
	/// </summary>
	UPROPERTY(Replicated)
	int RifleNum = 0;

	/// <summary>
	/// 확보 가능한 최대 Rifle 수
	/// </summary>
	UPROPERTY()
	int MaxRifleNum = 4;

	/// <summary>
	/// 현재 확보한 Bomb 수
	/// </summary>
	UPROPERTY(Replicated)
	int BombNum = 0;

	/// <summary>
	/// 확보 가능한 최대 Bomb 수
	/// </summary>
	UPROPERTY()
	int MaxBombNum = 1;

	/// <summary>
	/// Boss1Stage 클리어 유무
	/// </summary>
	UPROPERTY(Replicated)
	bool ClearBoss1Stage = false;

	/// <summary>
	/// Boss2Stage 클리어 유무
	/// </summary>
	UPROPERTY(Replicated)
	bool ClearBoss2Stage = false;

};
