// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "PlayerDataRow.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FPlayerDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FORCEINLINE FString GetName() const
	{
		return Name;
	}

	FORCEINLINE float GetHp() const
	{
		return Hp;
	}

	FORCEINLINE float GetMoveSpeed() const
	{
		return MoveSpeed;
	}

	FORCEINLINE float GetRotSpeed() const
	{
		return RotSpeed;
	}

	FORCEINLINE float GetRunSpeed() const
	{
		return RunSpeed;
	}

	FORCEINLINE bool GetJumping() const
	{
		return Jumping;
	}

	FORCEINLINE class USkeletalMesh* GetPlayerSkeletalMesh() const
	{
		return PlayerSkeletalMesh;
	}

	FORCEINLINE class USkeletalMesh* GetPlayerFPVPlayerSkeletalMesh() const
	{
		return FPVPlayerSkeletalMesh;
	}

	FORCEINLINE TSubclassOf<class UAnimInstance> GetPlayerAnimInstance() const
	{
		return PlayerAnimInstance;
	}

	FORCEINLINE TMap<EPlayerUpperState, class UAnimMontage*> GetAnimMontages() const
	{
		return AnimMontages;
	}

protected:

private:
	/// <summary>
	/// Player 이름
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString Name = "None";

	/// <summary>
	/// 체력
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float Hp = 100.0f;

	/// <summary>
	/// 이동 속도
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float MoveSpeed = 100.0f;

	/// <summary>
	/// 회전 속도
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RotSpeed = 100.0f;

	/// <summary>
	/// 뛰기 속도
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 2.0f;

	/// <summary>
	/// 점프 중
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	bool Jumping = false;

	/// <summary>
	/// 선택된 Player가 사용할 Skeletal Mesh
	/// </summary>
	UPROPERTY(Category = "PlayerSkeletalMesh", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	class USkeletalMesh* PlayerSkeletalMesh = nullptr;

	/// <summary>
	/// 선택된 Player가 사용할 1인칭 Skeletal Mesh
	/// </summary>
	UPROPERTY(Category = "PlayerSkeletalMesh", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	class USkeletalMesh* FPVPlayerSkeletalMesh = nullptr;

	/// <summary>
	/// 선택된 Player가 사용할 Anim Instance
	/// </summary>
	UPROPERTY(Category = "PlayerAnimInstance", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<class UAnimInstance> PlayerAnimInstance;

	/// <summary>
	/// Player 몽타주
	/// </summary>
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TMap<EPlayerUpperState, class UAnimMontage*> AnimMontages = TMap<EPlayerUpperState, class UAnimMontage*>();

};
