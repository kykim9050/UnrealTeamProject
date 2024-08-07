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

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(InputData->InputMapping, 0);

	if (nullptr != InputData->InputMapping)
	{
		EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &AMainPlayerController::MouseRotation);
		EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &AMainPlayerController::D_MoveRight);
		EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &AMainPlayerController::A_MoveLeft);
		EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &AMainPlayerController::W_MoveFront);
		EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &AMainPlayerController::S_MoveBack);
		EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, 0);
		EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, 1);
		EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Started, this, &AMainPlayerController::Num_ChangePosture, 2);
		EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_Drink);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Started, this, &AMainPlayerController::Num_BombSetStart);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_BombSetTick);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Completed, this, &AMainPlayerController::Num_BombSetEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[12], ETriggerEvent::Triggered, this, &AMainPlayerController::Num_ChangePosture, -1);
		EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Started, this, &AMainPlayerController::E_CheckItem);
		EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Started, this, &AMainPlayerController::P_ChangePOVController);
		EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &AMainPlayerController::LCtrl_Crouch);
		EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &AMainPlayerController::R_Reload);
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
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
	ChangePlayerDir(EPlayerMoveDir::Forward);
}

void AMainPlayerController::S_MoveBack(const FInputActionValue& Value)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	FVector Backward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Backward);
	ChangePlayerDir(EPlayerMoveDir::Back);
}

void AMainPlayerController::D_MoveRight(const FInputActionValue& Value)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
	ChangePlayerDir(EPlayerMoveDir::Right);
}

void AMainPlayerController::A_MoveLeft(const FInputActionValue& Value)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	FVector Leftward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Leftward);
	ChangePlayerDir(EPlayerMoveDir::Left);
}

void AMainPlayerController::MouseLeft_FireStart()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->AttackCheck();
	IsGunFire = true;

	// 발싸 신호를 HUD로 넘김.
	//BullitCountToHUD();
}

void AMainPlayerController::MouseLeft_FireTick(float _DeltaTime)
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	if (true == IsGunFire || Ch->GetIdleDefault() == EPlayerUpperState::Rifle_Idle)
	{
		//Ch->FireRayCast(_DeltaTime);
		Ch->AttackCheck();
	}

	// 발싸 신호를 HUD로 넘김.
	//BullitCountToHUD();
}

void AMainPlayerController::MouseLeft_FireEnd()
{
	IsGunFire = false;
}

void AMainPlayerController::E_CheckItem()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

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
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->CrouchCameraMove();
}

void AMainPlayerController::R_Reload()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->CharacterReload();
}

void AMainPlayerController::Num_ChangePosture(int _InputKey)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	if (_InputKey == 0) // 총
	{
		Ch->ChangeMontage(EPlayerUpperState::Rifle_Idle, true);
	}
	else if (_InputKey == 1)
	{
		Ch->ChangeMontage(EPlayerUpperState::Melee_Idle, true);
	}
	else if (_InputKey == -1)
	{
		Ch->ChangeMontage(EPlayerUpperState::UArm_Idle, true);
	}

	Ch->SettingItemSocket(_InputKey);

	//Ch->ChangeMontage(EPlayerUpperState::Rifle_Idle, true);
	//ChangePostureToWidget(_Posture);
}

void AMainPlayerController::Num_Drink()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->Drink();
}

void AMainPlayerController::Num_BombSetStart()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetStart();
}

void AMainPlayerController::Num_BombSetTick()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetTick();
}

void AMainPlayerController::Num_BombSetEnd()
{
	AMainCharacter* Ch = GetPawn<AMainCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetEnd();
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
