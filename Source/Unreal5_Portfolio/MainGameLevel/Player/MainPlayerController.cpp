// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Global/DataAssets/InputDatas.h"
#include "MainCharacter.h"

AMainPlayerController::AMainPlayerController()
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

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(InputData->InputMapping, 0);

	if (nullptr != InputData->InputMapping)
	{
		EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &AMainPlayerController::MouseRotation);
		EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &AMainPlayerController::MoveFront);
		EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &AMainPlayerController::MoveBack);
		EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &AMainPlayerController::MoveRight);
		EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &AMainPlayerController::MoveLeft);
		EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Triggered, this, &AMainPlayerController::Jump);
		EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &AMainPlayerController::JumpEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Started, this, &AMainPlayerController::FireStart);
		EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &AMainPlayerController::FireEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(0));
		EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(1));
		EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(2));
		EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(3));
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(4));
		EnhancedInputComponent->BindAction(InputData->Actions[12], ETriggerEvent::Triggered, this, &AMainPlayerController::ChangePosture, static_cast<EPlayerPosture>(5));
		EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Started, this, &AMainPlayerController::PickUpItem);
		EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Started, this, &AMainPlayerController::ChangePOVController);
	}
}

void AMainPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void AMainPlayerController::MoveFront(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
}

void AMainPlayerController::MoveBack(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Forward);
}

void AMainPlayerController::MoveRight(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
}

void AMainPlayerController::MoveLeft(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Rightward);
}

void AMainPlayerController::Jump(const FInputActionValue& Value)
{
}

void AMainPlayerController::JumpEnd(const FInputActionValue& Value)
{
}

void AMainPlayerController::FireStart(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Fire);

	BullitCountToHUD();


	GetWorld()->GetTimerManager().SetTimer(MyTimeHandle, FTimerDelegate::CreateLambda([&]()
		{
			FireTick(GetWorld()->GetTimeSeconds());
		}), 0.2f, true);
}

void AMainPlayerController::FireTick(float _DeltaTime)
{

}

void AMainPlayerController::FireEnd(const FInputActionValue& Value)
{
	ChangeState(EPlayerState::Idle);

	GetWorld()->GetTimerManager().ClearTimer(MyTimeHandle);
}

void AMainPlayerController::PickUpItem()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	
	Ch->PickUpItem();
}

void AMainPlayerController::ChangePOVController()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->ChangePOV();
}


void AMainPlayerController::ChangeState(EPlayerState _State)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

}

void AMainPlayerController::ChangePosture(EPlayerPosture _Posture)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

}

FGenericTeamId AMainPlayerController::GetGenericTeamId() const
{
	return TeamId;
}