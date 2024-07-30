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
	/// 확보된 Melee 수를 반환
	/// </summary>
	/// <returns></returns>
	FORCEINLINE int GetMeleeNum() const
	{
		return MeleeNum;
	}

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
	/// 현재 게임 진행 관련 체크 함수
	/// </summary>
	UFUNCTION(Reliable, NetMulticast)
	void GameStateCheck();
	void GameStateCheck_Implementation();

	UFUNCTION()
	FORCEINLINE int GetPlayerCount() const
	{
		return PlayerCount;
	}

	UFUNCTION()
	FORCEINLINE void AddPlayerCount()
	{
		++PlayerCount;
	}

	UFUNCTION()
	FORCEINLINE void SubPlayerCount()
	{
		if (0 >= PlayerCount)
		{
			PlayerCount = 0;
			return;
		}

		--PlayerCount;
	}


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

	/// <summary>
	/// 플레이어 수
	/// </summary>
	UPROPERTY(Replicated)
	int PlayerCount = 0;

	/// <summary>
	/// 플레이어 최대 수
	/// </summary>
	UPROPERTY()
	int MaxPlayerCount = 2;

};
