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

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FGetItemToWidget_Test.BindUObject(this, &ATestPlayerController::CallGetItem);
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
			EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveRight);
			EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveLeft);
			EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveFront);
			EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &ATestPlayerController::MoveBack);
			//EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Started, this, &ATestPlayerController::Jump);
			//EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &ATestPlayerController::JumpEnd);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Started, this, &ATestPlayerController::FireStart);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Triggered, this, &ATestPlayerController::FireTick);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &ATestPlayerController::FireEnd);
			EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture_Con, static_cast<EPlayerPosture>(0));	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture_Con, static_cast<EPlayerPosture>(1));	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture_Con, static_cast<EPlayerPosture>(2));	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &ATestPlayerController::Drink_Con);			// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Started, this, &ATestPlayerController::BombSetStart_Con);		// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Completed, this, &ATestPlayerController::BombSetCancel_Con);	// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[20], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePosture_Con, static_cast<EPlayerPosture>(5));	// => 메인 수정 필요 (24.07.30 해당 함수에 연동된 키 변경됨) ('0' -> 'X')
			EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Triggered, this, &ATestPlayerController::CheckItem_Con);		// => 메인 수정 필요 (24.07.29 해당 키에 연동된 함수 변경됨) (PickUpItem -> CheckItem)
			EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Triggered, this, &ATestPlayerController::ChangePOV_Con);		// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &ATestPlayerController::Crouch);
			EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &ATestPlayerController::IAReload);
		}
	}
}

void ATestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	PlayerIsFaint = Ch->IsFaint;
}

void ATestPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void ATestPlayerController::MoveFront(const FInputActionValue& Value)
{
	// 기절 상태 이동 불가능
	if (PlayerIsFaint == true)
	{
		return;
	}

	ChangeState_Con(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
	ChangePlayerDir(EPlayerMoveDir::Forward);
}

void ATestPlayerController::MoveBack(const FInputActionValue& Value)
{
	// 기절 상태 이동 불가능
	if (PlayerIsFaint == true)
	{
		return;
	}

	ChangeState_Con(EPlayerState::Walk);
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Forward);
	ChangePlayerDir(EPlayerMoveDir::Back);
}

void ATestPlayerController::MoveRight(const FInputActionValue& Value)
{
	// 기절 상태 이동 불가능
	if (PlayerIsFaint == true)
	{
		return;
	}

	ChangeState_Con(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
	ChangePlayerDir(EPlayerMoveDir::Right);
}

void ATestPlayerController::MoveLeft(const FInputActionValue& Value)
{
	// 기절 상태 이동 불가능
	if (PlayerIsFaint == true)
	{
		return;
	}

	ChangeState_Con(EPlayerState::Walk);
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Rightward);
	ChangePlayerDir(EPlayerMoveDir::Left);
}

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

void ATestPlayerController::Crouch(const FInputActionValue& Value)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	switch (Ch->LowerStateValue)
	{
	case EPlayerLowerState::Idle:
		Ch->CrouchCameraMove();
		Ch->ChangeLowerState(EPlayerLowerState::Crouch);
		break;
	case EPlayerLowerState::Crouch:
		Ch->CrouchCameraMove();
		Ch->ChangeLowerState(EPlayerLowerState::Idle);
		break;
	default:
		break;
	}
}

void ATestPlayerController::FireStart(float _DeltaTime)	// => 메인도 수정해야 함 (24.07.25 수정됨) => 메인 적용
{
	ChangeState_Con(EPlayerState::Fire);
	ATestCharacter* Ch = GetPawn<ATestCharacter>();

	if (Ch->CurItemIndex == 3 || Ch->CurItemIndex == 4)
	{
		return;
	}

	Ch->FireRayCast();
	AttackMontagePlay();
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, TEXT("Start"));
	GetWorld()->GetTimerManager().SetTimer(MyTimeHandle, FTimerDelegate::CreateLambda([&]()
		{
			FireTick(_DeltaTime);
		}), 0.2f, true);
}

void ATestPlayerController::FireTick(float _DeltaTime)	// => 메인도 수정해야 함 (24.07.25 수정됨) => 메인 적용
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->FireRayCast();
	++Count;
	AttackMontagePlay();
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, FString::Printf(TEXT("Tick Count : %d"), Count));
}

void ATestPlayerController::FireEnd()
{
	ChangeState_Con(EPlayerState::Idle);
	ATestCharacter* Ch = GetPawn<ATestCharacter>();

	//
	if (Ch->PostureValue == EPlayerPosture::Rifle1 || Ch->PostureValue == EPlayerPosture::Rifle2)
	{
		FireEndMontagePlay();
	}
	//

	GetWorld()->GetTimerManager().ClearTimer(MyTimeHandle);
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, TEXT("End"));
}

void ATestPlayerController::Drink_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->Drink();
}

void ATestPlayerController::BombSetStart_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->BombSetStart();
}

void ATestPlayerController::BombSetCancel_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->BombSetCancel();
}

void ATestPlayerController::CheckItem_Con()	// => 메인으로 이전 필요 (24.07.29 추가됨) => 메인 적용
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->CheckItem();
}

void ATestPlayerController::ChangeState_Con(EPlayerState _State)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeState(_State);
}

void ATestPlayerController::ChangePosture_Con(EPlayerPosture _Posture)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangePosture(_Posture);
	ChangePostureToWidget(_Posture);
}

void ATestPlayerController::ChangePOV_Con()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangePOV();
}

void ATestPlayerController::IAReload()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->CharacterReload();
}

void ATestPlayerController::ChangeLowerState(EPlayerLowerState _State)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeLowerState(_State);
}

void ATestPlayerController::ChangePlayerDir(EPlayerMoveDir _Dir)
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangePlayerDir(_Dir);
}

void ATestPlayerController::AttackMontagePlay()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeMontage(false);
}

void ATestPlayerController::FireEndMontagePlay()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeMontage(true);
}

void ATestPlayerController::SetFaint()
{
	ATestCharacter* Ch = GetPawn<ATestCharacter>();
	Ch->ChangeIsFaint();
}

FGenericTeamId ATestPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void ATestPlayerController::CallGetItem()
{
	CallGetItemToWidget();
}
