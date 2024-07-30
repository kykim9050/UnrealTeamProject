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
		EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &AMainPlayerController::W_MoveFront);
		EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &AMainPlayerController::S_MoveBack);
		EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &AMainPlayerController::D_MoveRight);
		EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &AMainPlayerController::A_MoveLeft);
		EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Triggered, this, &AMainPlayerController::Spase_Jump);
		EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &AMainPlayerController::Spase_JumpEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Started, this, &AMainPlayerController::MouseLeft_FireStart);
		EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &AMainPlayerController::MouseLeft_FireEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, static_cast<EPlayerPosture>(0));
		EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, static_cast<EPlayerPosture>(1));
		EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, static_cast<EPlayerPosture>(2));
		EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_Drink_Con);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_BombSetStart);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Completed, this, &AMainPlayerController::Num_BombSetEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[12], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_ChangePosture, static_cast<EPlayerPosture>(5));
		EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Started, this, &AMainPlayerController::E_CheckItem);
		EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Started, this, &AMainPlayerController::P_ChangePOVController);
		EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &AMainPlayerController::LCtrl_Crouch);
		EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &AMainPlayerController::R_Reload);
		// 17 - G
	}
}

void AMainPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void AMainPlayerController::W_MoveFront(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
	ChangePlayerDir(EPlayerMoveDir::Forward);
}

void AMainPlayerController::S_MoveBack(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Forward);
	ChangePlayerDir(EPlayerMoveDir::Back);
}

void AMainPlayerController::D_MoveRight(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
	ChangePlayerDir(EPlayerMoveDir::Right);
}

void AMainPlayerController::A_MoveLeft(const FInputActionValue& Value)
{
	if (CharacterIsFaint == true)
	{
		return;
	}

	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Rightward);
	ChangePlayerDir(EPlayerMoveDir::Left);
}

void AMainPlayerController::Spase_Jump(const FInputActionValue& Value)
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

void AMainPlayerController::Spase_JumpEnd(const FInputActionValue& Value)
{
	ACharacter* MyPlayerState = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (nullptr == MyPlayerState)
	{
		return;
	}

	MyPlayerState->StopJumping();
}

void AMainPlayerController::MouseLeft_FireStart(const FInputActionValue& Value)
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
			MouseLeft_FireTick(GetWorld()->GetTimeSeconds());
		}), 0.2f, true);
}

void AMainPlayerController::MouseLeft_FireTick(float _DeltaTime)
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

void AMainPlayerController::MouseLeft_FireEnd(const FInputActionValue& Value)
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimeHandle);
}

void AMainPlayerController::E_CheckItem()
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

	Ch->CheckItem();
}

void AMainPlayerController::P_ChangePOVController()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->ChangePOV();
}

void AMainPlayerController::LCtrl_Crouch(const FInputActionValue& Value)
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

void AMainPlayerController::R_Reload()
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

void AMainPlayerController::Num_ChangePosture(EPlayerPosture _Posture)
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

void AMainPlayerController::Num_Drink_Con()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	//Ch->Drink();
}

void AMainPlayerController::Num_BombSetStart()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	//Ch->BombSetStart();
}

void AMainPlayerController::Num_BombSetEnd()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	//Ch->BombSetEnd();
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
