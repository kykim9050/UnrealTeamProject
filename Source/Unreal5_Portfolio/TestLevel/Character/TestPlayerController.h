// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/ContentsEnum.h"
#include "GenericTeamAgentInterface.h"
#include "TestPlayerController.generated.h"

DECLARE_DELEGATE(FDelegate_Reload);
DECLARE_DELEGATE(FDelegate_GetItem);
DECLARE_DELEGATE_OneParam(FDelegate_Faint, const bool);

/**
 *
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ATestPlayerController();
protected:
	void BeginPlay() override;

public:
	FDelegate_Reload FCharacterToReload;
	FDelegate_Faint FCharacterToFaint;
	FDelegate_GetItem FGetItemToWidget;


	UFUNCTION(BlueprintCallable)
	void SetupInputComponent() override;

	// Input Actions
	UFUNCTION(BlueprintCallable)
	void MouseRotation(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void W_MoveFront(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void S_MoveBack(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void D_MoveRight(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void A_MoveLeft(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireStart();
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireTick(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireEnd();
	UFUNCTION(BlueprintCallable)
	void E_CheckItem();
	UFUNCTION(BlueprintCallable)
	void P_ChangePOVController();
	UFUNCTION(BlueprintCallable)
	void LCtrl_Crouch(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void R_Reload();

	// Number Key
	UFUNCTION(BlueprintCallable)
	void Num_ChangePosture(int _InputKey);
	UFUNCTION(BlueprintCallable)
	void Num_Drink();
	UFUNCTION(BlueprintCallable)
	void Num_BombSetStart();
	UFUNCTION(BlueprintCallable)
	void Num_BombSetTick();
	UFUNCTION(BlueprintCallable)
	void Num_BombSetEnd();

	// 하체
	UFUNCTION(BlueprintCallable)
	void ChangeLowerState(EPlayerLowerState _State);

	// 플레이어 방향
	UFUNCTION(BlueprintCallable)
	void ChangePlayerDir(EPlayerMoveDir _Dir);

	// Generic Team Id
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	// Input
	UPROPERTY()
	class UInputDatas* InputData = nullptr;

	// Fire 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsGunFire = false;

	// Camera Shake
	UPROPERTY()
	ECameraShakeState ShakeState = ECameraShakeState::Stop;
	UPROPERTY()
	FVector ShakeValue = FVector(0.0f, 0.0f, 0.0f);

	UFUNCTION()
	void ResetCameraShakeValue();
	UFUNCTION()
	void ChangeCameraShakeState(ECameraShakeState _ShakeState);
	UFUNCTION(BlueprintCallable)
	void CameraShakeTick(float _DeltaTime);

	// Monster 요청
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TeamId", meta = (AllowPrivateAccess = true))
	FGenericTeamId TeamId;

	// 기절 상태.
	UPROPERTY()
	bool CharacterIsFaint = false;

	UFUNCTION()
	void CallReload();

	UFUNCTION()
	void CallFaint(bool _Faint);

	UFUNCTION()
	void CallGetItem();

protected:
	// Bullet Count To HUD [BP]
	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void BullitCountToHUD();

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void ChangePostureToWidget(EPlayerUpperState _Posture);

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void CallGetItemToWidget();
};
