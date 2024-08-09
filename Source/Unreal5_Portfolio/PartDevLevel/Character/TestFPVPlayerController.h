// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/ContentsEnum.h"
#include "GenericTeamAgentInterface.h"
#include "TestFPVPlayerController.generated.h"

DECLARE_DELEGATE(FDelegate_GetItem_Test_FPV);

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestFPVPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ATestFPVPlayerController();

	FDelegate_GetItem_Test_FPV FGetItemToWidget_Test_FPV;

protected:
	void BeginPlay() override;

public :

	// Input
	UPROPERTY()
	class UInputDatas* InputData;

	UFUNCTION(BlueprintCallable)
	void SetupInputComponent() override;

	UFUNCTION()
	void PlayerTick(float DeltaTime) override;

	// Actions
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
	
	//UFUNCTION(BlueprintCallable)
	//void Jump(const FInputActionValue& Value);
	//UFUNCTION(BlueprintCallable)
	//void JumpEnd(const FInputActionValue& Value);

	// 사용 중 (태환)
	UFUNCTION(BlueprintCallable)
	void Crouch(const FInputActionValue& Value);

	// Fire
	UFUNCTION(BlueprintCallable)
	void FireStart(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void FireTick(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void FireEnd();

	// Drink
	UFUNCTION(BlueprintCallable)
	void Drink_Con();	// => 메인에 추후 이전해야 함 (24.07.30 함수 이름 수정, 테스팅 중) => 메인 적용(주석)

	// Bomb Setting
	UFUNCTION(BlueprintCallable)
	void BombSetStart_Con();	// => 메인에 추후 이전해야 함 (24.07.30 함수 이름 수정, 테스팅 중) => 메인 적용(주석)
	UFUNCTION(BlueprintCallable)
	void BombSetTick_Con();		// => 메인에 추후 이전해야 함 (24.07.31 추가됨, 테스팅 중)
	UFUNCTION(BlueprintCallable)
	void BombSetCancel_Con();	// => 메인에 추후 이전해야 함 (24.07.30 함수 이름 수정, 테스팅 중) => 메인 적용(주석)

	// Item
	UFUNCTION(BlueprintCallable)
	void CheckItem_Con();	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨) (PickUpItem 함수 대체) => 메인 적용

	// Posture
	UFUNCTION(BlueprintCallable)
	void ChangePosture_Con(int _InputKey);
	//void ChangePosture_Con(EPlayerPosture _Posture);	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨) => 메인 적용

	// POV
	UFUNCTION(BlueprintCallable)
	void ChangePOV_Con();	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨) => 메인 적용

	// Reload (k)
	UFUNCTION(BlueprintCallable)
	void IAReload();

	// LowerStateChange 함수 (태환) => 메인 적용
	//UFUNCTION(BlueprintCallable)
	//void ChangeLowerState(EPlayerLowerState _State);

	// PlayerDirChange 함수 (태환) => 메인 적용
	UFUNCTION(BlueprintCallable)
	void ChangePlayerDir(EPlayerMoveDir _Dir);

	// 공격 몽타주 변경 함수  => 메인 적용
	//UFUNCTION(BlueprintCallable)
	//void PlayerMontagePlay();

	// 공격 종료 몽타주 변경 함수  => 메인 적용
	//UFUNCTION(BlueprintCallable)
	//void FireEndMontagePlay();

	//테스트용
	UFUNCTION(BlueprintCallable)
	void SetFaint();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TeamId", meta = (AllowPrivateAccess = true))
	FGenericTeamId TeamId; // => 메인 적용
	virtual FGenericTeamId GetGenericTeamId() const override; // => 메인 적용

	FTimerHandle MyTimeHandle; // => 메인 적용
	int Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PlayerIsFaint = false; // => 메인 적용(Delegate)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PlayerIsBombSetting = false; // 메인 적용 필요

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsGunFire = false;

	// Camera(Controller) Shake
	UPROPERTY()
	FRandomStream Stream;

	// HUD / Widget
	UFUNCTION()
	void CallGetItem(); // => 메인 적용(Delegate)

protected: // => 메인 적용(Delegate)
	//UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	//void ChangePostureToWidget(EPlayerPosture _Posture);

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void GetItemToWidget();

	UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void CallGetItemToWidget();
};
