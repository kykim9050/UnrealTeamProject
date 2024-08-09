// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UPlayerAnimInstance : public UMainAnimInstance
{
	GENERATED_BODY()

public:
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;

	void ChangeAnimation(EPlayerUpperState _Posture);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ATestCharacter* OwnerPlayer = nullptr;
	//class AMainCharacter* OwnerPlayer = nullptr; // main - kjb
	//class ATestFPVCharacter* OwnerPlayer = nullptr; // TestPlayer - kjb

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//EPlayerPosture PlayerPosture = EPlayerPosture::Barehand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState PlayerLowerState = EPlayerLowerState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerUpperState PlayerUppperState = EPlayerUpperState::UArm_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir PlayerDir = EPlayerMoveDir::Forward;

	// 7/26 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PlayerIsFaint = false;

	// 7/31 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PlayerIsBombSetting = false;

	class UMainGameInstance* MainGameInst;
};
