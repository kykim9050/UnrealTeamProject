// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/ContentsEnum.h"
#include "GenericTeamAgentInterface.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public :
	AMainPlayerController();

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
	void FireStart(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void FireTick(float _DeltaTime);
	UFUNCTION(BlueprintCallable)
	void FireEnd();
	UFUNCTION(BlueprintCallable)
	void PickUpItem();

	// State, Posture
	UFUNCTION(BlueprintCallable)
	void ChangeState(EPlayerState _State);
	UFUNCTION(BlueprintCallable)
	void ChangePosture(EPlayerPosture _Posture);

	// Generic Team Id
	virtual FGenericTeamId GetGenericTeamId() const override;

private :
	// Input
	UPROPERTY()
	class UInputDatas* InputData = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TeamId", meta = (AllowPrivateAccess = true))
	FGenericTeamId TeamId;
};
