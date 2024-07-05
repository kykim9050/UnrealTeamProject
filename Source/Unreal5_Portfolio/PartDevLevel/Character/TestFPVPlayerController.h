// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/ContentsEnum.h"
#include "GenericTeamAgentInterface.h"
#include "TestFPVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATestFPVPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ATestFPVPlayerController();

	// Input
	UPROPERTY()
	class UInputDatas* InputData;

	UFUNCTION(BlueprintCallable)
	void SetupInputComponent() override;

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
	UFUNCTION(BlueprintCallable)
	void Jump(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void JumpEnd(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Fire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void FireEnd(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void PickUpItem();
	UFUNCTION(BlueprintCallable)
	void PickUpItemEnd();

	// State, Posture
	UFUNCTION(BlueprintCallable)
	void ChangeState(EPlayerState _State);
	UFUNCTION(BlueprintCallable)
	void ChangePostureController(EPlayerPosture _Posture);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TeamId", meta = (AllowPrivateAccess = true))
	FGenericTeamId TeamId;
	virtual FGenericTeamId GetGenericTeamId() const override;
};