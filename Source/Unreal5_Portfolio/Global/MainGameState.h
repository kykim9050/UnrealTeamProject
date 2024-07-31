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
	/// 현재 게임 진행 관련 체크 함수
	/// </summary>
	UFUNCTION(Reliable, NetMulticast)
	void GameStateCheck(AActor* _OtherActor);
	void GameStateCheck_Implementation(AActor* _OtherActor);

	/// <summary>
	/// 인자(AActor)의 대상에 대한 정보로 GameState 변수 조정
	/// </summary>
	/// <param name="_OtherActor"></param>
	UFUNCTION(Reliable, NetMulticast)
	void GameStateModify(AActor* _OtherActor);
	void GameStateModify_Implementation(AActor* _OtherActor);

	/// <summary>
	/// GameState 변수 정보 갱신 함수
	/// </summary>
	/// <param name="_OtherActor"></param>
	UFUNCTION()
	void GameStateConditionUpdate(AActor* _OtherActor, bool _IsAdd);

	UFUNCTION()
	FORCEINLINE int GetPlayerCount()
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

	UFUNCTION()
	FORCEINLINE bool GetIsStageChange() const
	{
		return IsStageChange;
	}

	UFUNCTION()
	FORCEINLINE void SetIsStageChange(bool _Value)
	{
		IsStageChange = _Value;
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
	/// 게임 Stage가 바뀌었는지에 대한 유무 변수
	/// </summary>
	UPROPERTY()
	bool IsStageChange = false;

	/// <summary>
	/// 현재 확보한 Bomb 수
	/// </summary>
	UPROPERTY()
	int BombCount = 0;

	/// <summary>
	/// 확보 가능한 최대 Bomb 수
	/// </summary>
	UPROPERTY()
	int MaxBombCount = 1;

	/// <summary>
	/// 플레이어 수
	/// </summary>
	UPROPERTY()
	int PlayerCount = 0;

	/// <summary>
	/// 플레이어 최대 수
	/// </summary>
	UPROPERTY()
	int MaxPlayerCount = 2;

	/// <summary>
	/// 체크할 아이템 카운트 수
	/// </summary>
	UPROPERTY()
	int ItemCount = 0;
};
