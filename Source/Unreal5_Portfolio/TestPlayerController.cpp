// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//#include "EnhancedActionKeyMapping.h"
//#include "InputAction.h"
//#include "InputMappingContext.h"
//#include "UE_Project/Global/InputActionDatas.h"
//#include "ATestCharacter.h"
//
//ATestPlayerController::ATestPlayerController()
//{
//	{
//		FString RefPathString = TEXT("InputActionDatas'/Game/Resources/FPVLevel/Data/FPVInputDataAsset.FPVInputDataAsset'");
//		ConstructorHelpers::FObjectFinder<UInputActionDatas> ResPath(*RefPathString);
//
//		if (false == ResPath.Succeeded())
//		{
//			return;
//		}
//
//		InputData = ResPath.Object;
//	}
//}
//
//void ATestPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//
//	FInputModeGameOnly InputMode;
//	SetInputMode(InputMode);
//
//	{
//		UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
//		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
//
//		InputSystem->ClearAllMappings();
//		InputSystem->AddMappingContext(InputData->InputMapping, 0);
//
//		if (nullptr != InputData->InputMapping)
//		{
//			EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &AFPVPlayerController::MouseRotation);
//			EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &AFPVPlayerController::MoveFront);
//			EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &AFPVPlayerController::MoveBack);
//			EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &AFPVPlayerController::MoveRight);
//			EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &AFPVPlayerController::MoveLeft);
//			EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Triggered, this, &AFPVPlayerController::Jump);
//			EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &AFPVPlayerController::JumpEnd);
//			EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Triggered, this, &AFPVPlayerController::Fire);
//			EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &AFPVPlayerController::FireEnd);
//		}
//	}
//}
//
//void ATestPlayerController::MouseRotation(const FInputActionValue& Value)
//{
//	FVector2D MouseXY = Value.Get<FVector2D>();
//	AddYawInput(MouseXY.X);
//	AddPitchInput(-MouseXY.Y);
//}
//
//void ATestPlayerController::MoveFront(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Walk);
//	FVector Forward = GetPawn()->GetActorForwardVector();
//	GetPawn()->AddMovementInput(Forward);
//}
//
//void ATestPlayerController::MoveBack(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Walk);
//	FVector Forward = GetPawn()->GetActorForwardVector();
//	GetPawn()->AddMovementInput(-Forward);
//}
//
//void ATestPlayerController::MoveRight(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Walk);
//	FVector Rightward = GetPawn()->GetActorRightVector();
//	GetPawn()->AddMovementInput(Rightward);
//}
//
//void ATestPlayerController::MoveLeft(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Walk);
//	FVector Rightward = GetPawn()->GetActorRightVector();
//	GetPawn()->AddMovementInput(-Rightward);
//}
//
//void ATestPlayerController::Jump(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Jump);
//	ATestCharacter* Ch = GetPawn<ATestCharacter>();
//	Ch->Jump();
//}
//
//void ATestPlayerController::JumpEnd(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Idle);
//	ATestCharacter* Ch = GetPawn<ATestCharacter>();
//	Ch->StopJumping();
//}
//
//void ATestPlayerController::Fire(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Fire);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fire!"));
//}
//
//void ATestPlayerController::FireEnd(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Idle);
//}
//
//void ATestPlayerController::ChangeState(EPlayerState _State)
//{
//	ATestCharacter* Ch = GetPawn<ATestCharacter>();
//	Ch->ChangeState(_State);
//}