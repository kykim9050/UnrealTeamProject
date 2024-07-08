// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedActionKeyMapping.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Global/DataAssets/InputDatas.h"
#include "TestCharacter.h"

ATestPlayerController::ATestPlayerController()
{
	TeamId = FGenericTeamId(0);
	{
		FString RefPathString = TEXT("InputDatas'/Game/Resources/Global/DataAssets/DA_InputDatas.DA_InputDatas'");
		ConstructorHelpers::FObjectFinder<UInputDatas> ResPath(*RefPathString);

		if (false == ResPath.Succeeded())
		{
			return;
		}

		InputData = ResPath.Object;
	}
}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		InputSystem->ClearAllMappings();
		InputSystem->AddMappingContext(InputData->InputMapping, 0);

		if (nullptr != InputData->InputMapping)
		{
			EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &ATestPlayerController::MouseRotation);
			EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveFront);
			EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveBack);
			EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveRight);
			EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveLeft);
			EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Triggered, this, &ATestPlayerController::Jump);
			EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &ATestPlayerController::JumpEnd);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Started, this, &ATestPlayerController::FireStart);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Triggered, this, &ATestPlayerController::FireTick);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &ATestPlayerController::FireEnd);
			EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(0));
			EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(1));
			EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(2));
			EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(3));
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(4));
			EnhancedInputComponent->BindAction(InputData->Actions[12], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture, static_cast<EPlayerPosture>(5));
			EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Triggered, this, &ATestPlayerController::PickUpItem);
			EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Completed, this, &ATestPlayerController::PickUpItemEnd);
		}
	}
}

void ATestPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void ATestPlayerController::MoveFront(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
}

void ATestPlayerController::MoveBack(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Forward);
}

void ATestPlayerController::MoveRight(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
}

void ATestPlayerController::MoveLeft(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Rightward);
}

void ATestPlayerController::Jump(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Jump);
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->Jump();
}

void ATestPlayerController::JumpEnd(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Idle);
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->StopJumping();
}

//void ATestPlayerController::FireStart(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Fire);
//}
//void ATestPlayerController::FireTick(const FInputActionValue& Value)
//{
//	//ChangeState(EPlayerState::Fire);
//}
//void ATestPlayerController::FireEnd(const FInputActionValue& Value)
//{
//	ChangeState(EPlayerState::Idle);
//}

void ATestPlayerController::FireStart(float _DeltaTime)
{
	ChangeState(EPlayerState::Fire);
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->FireRayCast(_DeltaTime);
}

void ATestPlayerController::FireTick(float _DeltaTime)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->FireRayCast(_DeltaTime);
}

void ATestPlayerController::FireEnd()
{
	ChangeState(EPlayerState::Idle);
}

void ATestPlayerController::PickUpItem()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	FString Name = Ch->GetRayCastToItemName();
	if (Name == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Not Item"));
		return;
	}

	Ch->PickUpItem(FName(Name));
	Ch->SetPickUp(true);
}

void ATestPlayerController::PickUpItemEnd()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->SetPickUp(false);
}

void ATestPlayerController::ChangeState(EPlayerState _State)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeState(_State);
}

void ATestPlayerController::ChangePosture(EPlayerPosture _Posture)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangePosture(_Posture);
}

FGenericTeamId ATestPlayerController::GetGenericTeamId() const
{
	return TeamId;
}
