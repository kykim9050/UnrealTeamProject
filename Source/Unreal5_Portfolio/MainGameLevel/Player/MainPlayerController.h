// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/ContentsEnum.h"
#include "GenericTeamAgentInterface.h"
#include "MainPlayerController.generated.h"

DECLARE_DELEGATE(FDelegate_Reload);
DECLARE_DELEGATE(FDelegate_GetItem);
DECLARE_DELEGATE_OneParam(FDelegate_Faint, const bool);

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public :
	AMainPlayerController();
protected :
	void BeginPlay() override;

public :
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
	void Spase_Jump(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Spase_JumpEnd(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireStart(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireTick(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void MouseLeft_FireEnd(const FInputActionValue& Value);
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
	void Num_ChangePosture(EPlayerPosture _Posture);
	UFUNCTION(BlueprintCallable)
	void Num_Drink_Con();
	UFUNCTION(BlueprintCallable)
	void Num_BombSetStart();
	UFUNCTION(BlueprintCallable)
	void Num_BombSetEnd();

	// 하체
	UFUNCTION(BlueprintCallable)
	void ChangeLowerState(EPlayerLowerState _State);

	// 플레이어 방향
	UFUNCTION(BlueprintCallable)
	void ChangePlayerDir(EPlayerMoveDir _Dir);

	// 공격 몽타주 실행
	UFUNCTION(BlueprintCallable)
	void PlayerMontagePlay();

	// 공격 종료 몽타주 실행
	UFUNCTION(BlueprintCallable)
	void FireEndMontagePlay();

	// Generic Team Id
	virtual FGenericTeamId GetGenericTeamId() const override;

private :
	// Input
	UPROPERTY()
	class UInputDatas* InputData = nullptr;

	// Monster 요청
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TeamId", meta = (AllowPrivateAccess = true))
	FGenericTeamId TeamId;

	// Fire Tick 함수를 위한 Timer 변수.
	UPROPERTY()
	FTimerHandle MyTimeHandle;

	// 기절 상태.
	UPROPERTY()
	bool CharacterIsFaint = false;

	UFUNCTION()
	void CallReload();

	UFUNCTION()
	void CallFaint(bool _Faint);

	UFUNCTION()
	void CallGetItem();

protected :
	// Bullet Count To HUD [BP]
	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void BullitCountToHUD();

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void ChangePostureToWidget(EPlayerPosture _Posture);

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void CallGetItemToWidget();
};
