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

	void ChangeAnimation(EPlayerPosture _Posture);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ATestCharacter* OwnerPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PlayerPosture = EPlayerPosture::Barehand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState PlayerLowerState = EPlayerLowerState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir PlayerDir = EPlayerMoveDir::Forward;

	class UMainGameInstance* MainGameInst;
};
