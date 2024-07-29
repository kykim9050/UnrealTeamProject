// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Player/MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Global/DataAssets/InputDatas.h"
#include "MainCharacter.h"

#include "Kismet/GameplayStatics.h"

AMainPlayerController::AMainPlayerController()
{
	TeamId = FGenericTeamId(0);
	{
		FString RefPathString = TEXT("InputDatas'/Game/Resources/Global/DataAssets/DA_MainInputDatas.DA_MainInputDatas'");
		ConstructorHelpers::FObjectFinder<UInputDatas> ResPath(*RefPathString);

		if (false == ResPath.Succeeded())
		{
			return;
		}

		InputData = ResPath.Object;
	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FCharacterToReload.BindUObject(this, &AMainPlayerController::CallReload);
	FCharacterToFaint.BindUObject(this, &AMainPlayerController::CallFaint);
	FGetItemToWidget.BindUObject(this, &AMainPlayerController::CallGetItem);
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
		EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &AMainPlayerController::Crouch);
		EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &AMainPlayerController::IAReload);
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
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
	ChangePlayerDir(EPlayerMoveDir::Forward);
}

void AMainPlayerController::MoveBack(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Forward);
	ChangePlayerDir(EPlayerMoveDir::Back);
}

void AMainPlayerController::MoveRight(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
	ChangePlayerDir(EPlayerMoveDir::Right);
}

void AMainPlayerController::MoveLeft(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Rightward);
	ChangePlayerDir(EPlayerMoveDir::Left);
}

void AMainPlayerController::Jump(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	ChangeLowerState(EPlayerLowerState::Idle);

	ACharacter* MyPlayerState = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (nullptr == MyPlayerState)
	{
		return;
	}

	MyPlayerState->Jump();
}

void AMainPlayerController::JumpEnd(const FInputActionValue& Value)
{
	ACharacter* MyPlayerState = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (nullptr == MyPlayerState)
	{
		return;
	}

	MyPlayerState->StopJumping();
}

void AMainPlayerController::FireStart(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->FireRayCast(GetWorld()->GetTimeSeconds());

	AttackMontagePlay();

	// ¹ß½Î ½ÅÈ£¸¦ HUD·Î ³Ñ±è.
	BullitCountToHUD();

	GetWorld()->GetTimerManager().SetTimer(MyTimeHandle, FTimerDelegate::CreateLambda([&]()
		{
			FireTick(GetWorld()->GetTimeSeconds());
		}), 0.2f, true);
}

void AMainPlayerController::FireTick(float _DeltaTime)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->FireRayCast(_DeltaTime);

	AttackMontagePlay();

	// ¹ß½Î ½ÅÈ£¸¦ HUD·Î ³Ñ±è.
	BullitCountToHUD();
}

void AMainPlayerController::FireEnd(const FInputActionValue& Value)
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimeHandle);
}

void AMainPlayerController::PickUpItem()
{
	if (CharacterIsFaint == true)
	{
		return;
	}

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

void AMainPlayerController::Crouch(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	switch (Ch->LowerStateValue)
	{
	case EPlayerLowerState::Idle:
		Ch->ChangeLowerState(EPlayerLowerState::Crouch);
		break;
	case EPlayerLowerState::Crouch:
		Ch->ChangeLowerState(EPlayerLowerState::Idle);
		break;
	default:
		break;
	}
	Ch->CrouchCameraMove();
}

void AMainPlayerController::IAReload()
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->CharacterReload();
}

void AMainPlayerController::ChangePosture(EPlayerPosture _Posture)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangePosture(_Posture);
	ChangePostureToWidget(_Posture);
}

void AMainPlayerController::ChangeLowerState(EPlayerLowerState _State)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangeLowerState(_State);
}

void AMainPlayerController::ChangePlayerDir(EPlayerMoveDir _Dir)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangePlayerDir(_Dir);
}

void AMainPlayerController::AttackMontagePlay()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangeMontage(false);
}

void AMainPlayerController::FireEndMontagePlay()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangeMontage(true);
}

FGenericTeamId AMainPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void AMainPlayerController::CallReload()
{
	BullitCountToHUD();
}

void AMainPlayerController::CallFaint(bool _Faint)
{
	CharacterIsFaint = _Faint;
}

void AMainPlayerController::CallGetItem()
{
	CallGetItemToWidget();
}
