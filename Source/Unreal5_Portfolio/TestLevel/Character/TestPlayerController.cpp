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
		FString RefPathString = TEXT("InputDatas'/Game/Resources/Global/DataAssets/DA_MainInputDatas.DA_MainInputDatas'");
		ConstructorHelpers::FObjectFinder<UInputDatas> ResPath(*RefPathString);

		if (false == ResPath.Succeeded())
		{
			return;
		}

		InputData = ResPath.Object;
	}
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FCharacterToReload.BindUObject(this, &ATestPlayerController::CallReload);
	FCharacterToFaint.BindUObject(this, &ATestPlayerController::CallFaint);
	FGetItemToWidget.BindUObject(this, &ATestPlayerController::CallGetItem);
}

void ATestPlayerController::SetupInputComponent()
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
		EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &ATestPlayerController::MouseRotation);
		EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &ATestPlayerController::D_MoveRight);
		EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &ATestPlayerController::A_MoveLeft);
		EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &ATestPlayerController::W_MoveFront);
		EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &ATestPlayerController::S_MoveBack);
		EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Started, this, &ATestPlayerController::Num_ChangePosture, 0);
		EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Started, this, &ATestPlayerController::Num_ChangePosture, 1);
		EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Started, this, &ATestPlayerController::Num_ChangePosture, 2);
		EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &ATestPlayerController::Num_Drink);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Started, this, &ATestPlayerController::Num_BombSetStart);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &ATestPlayerController::Num_BombSetTick);
		EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Completed, this, &ATestPlayerController::Num_BombSetEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[12], ETriggerEvent::Triggered, this, &ATestPlayerController::Num_ChangePosture, -1);
		EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Started, this, &ATestPlayerController::E_CheckItem);
		EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Started, this, &ATestPlayerController::P_ChangePOVController);
		EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &ATestPlayerController::LCtrl_Crouch);
		EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &ATestPlayerController::R_Reload);
	}
}

void ATestPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void ATestPlayerController::W_MoveFront(const FInputActionValue& Value)
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

void ATestPlayerController::S_MoveBack(const FInputActionValue& Value)
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

void ATestPlayerController::D_MoveRight(const FInputActionValue& Value)
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

void ATestPlayerController::A_MoveLeft(const FInputActionValue& Value)
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

void ATestPlayerController::MouseLeft_FireStart()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->AttackCheck();
	IsGunFire = true;

	// 발싸 신호를 HUD로 넘김.
	//BullitCountToHUD();
}

void ATestPlayerController::MouseLeft_FireTick(float _DeltaTime)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
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

void ATestPlayerController::MouseLeft_FireEnd()
{
	IsGunFire = false;
}

void ATestPlayerController::E_CheckItem()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->CheckItem();
}

void ATestPlayerController::P_ChangePOVController()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->ChangePOV();
}

void ATestPlayerController::LCtrl_Crouch(const FInputActionValue& Value)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->CrouchCameraMove();
}

void ATestPlayerController::R_Reload()
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->CharacterReload();
}

void ATestPlayerController::Num_ChangePosture(int _InputKey)
{
	// 기절 상태
	//if (CharacterIsFaint == true)
	//{
	//	return;
	//}

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
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

void ATestPlayerController::Num_Drink()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->Drink();
}

void ATestPlayerController::Num_BombSetStart()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetStart();
}

void ATestPlayerController::Num_BombSetTick()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetTick();
}

void ATestPlayerController::Num_BombSetEnd()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->BombSetEnd();
}

void ATestPlayerController::ChangeLowerState(EPlayerLowerState _State)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangeLowerState(_State);
}

void ATestPlayerController::ChangePlayerDir(EPlayerMoveDir _Dir)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->ChangePlayerDir(_Dir);
}

FGenericTeamId ATestPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void ATestPlayerController::CallReload()
{
	BullitCountToHUD();
}

void ATestPlayerController::CallFaint(bool _Faint)
{
	CharacterIsFaint = _Faint;
}

void ATestPlayerController::CallGetItem()
{
	CallGetItemToWidget();
}
