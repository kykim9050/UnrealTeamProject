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
	void MoveFront(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MoveBack(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MoveRight(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void MoveLeft(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Jump(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void JumpEnd(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void FireStart(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void FireTick(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void FireEnd(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void PickUpItem();
	UFUNCTION(BlueprintCallable)
	void ChangePOVController();
	UFUNCTION(BlueprintCallable)
	void Crouch(const FInputActionValue& Value);
	// Reload (k)
	UFUNCTION(BlueprintCallable)
	void IAReload();


	// Posture
	UFUNCTION(BlueprintCallable)
	void ChangePosture(EPlayerPosture _Posture);

	// 하체
	UFUNCTION(BlueprintCallable)
	void ChangeLowerState(EPlayerLowerState _State);

	// 플레이어 방향
	UFUNCTION(BlueprintCallable)
	void ChangePlayerDir(EPlayerMoveDir _Dir);

	// 공격
	UFUNCTION(BlueprintCallable)
	void AttackMontagePlay();

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
