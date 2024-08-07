// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/TestFPVPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedActionKeyMapping.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Global/DataAssets/InputDatas.h"
#include "TestFPVCharacter.h"

ATestFPVPlayerController::ATestFPVPlayerController()
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

void ATestFPVPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FGetItemToWidget_Test_FPV.BindUObject(this, &ATestFPVPlayerController::CallGetItem);

	// Camera(Controller) Shake
	Stream.GenerateNewSeed();
}

void ATestFPVPlayerController::SetupInputComponent()
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
			EnhancedInputComponent->BindAction(InputData->Actions[0], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::MouseRotation);
			EnhancedInputComponent->BindAction(InputData->Actions[3], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::MoveRight);
			EnhancedInputComponent->BindAction(InputData->Actions[4], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::MoveLeft);
			EnhancedInputComponent->BindAction(InputData->Actions[1], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::MoveFront);
			EnhancedInputComponent->BindAction(InputData->Actions[2], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::MoveBack);
			//EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Started, this, &ATestPlayerController::Jump);
			//EnhancedInputComponent->BindAction(InputData->Actions[5], ETriggerEvent::Completed, this, &ATestPlayerController::JumpEnd);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Started, this, &ATestPlayerController::FireStart);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Triggered, this, &ATestPlayerController::FireTick);
			//EnhancedInputComponent->BindAction(InputData->Actions[6], ETriggerEvent::Completed, this, &ATestPlayerController::FireEnd);
			EnhancedInputComponent->BindAction(InputData->Actions[7], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::ChangePosture_Con, 0);	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[8], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::ChangePosture_Con, 1);	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[9], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::ChangePosture_Con, 2);	// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[10], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::Drink_Con);			// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Started, this, &ATestFPVPlayerController::BombSetStart_Con);		// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::BombSetTick_Con);	// => 메인 이전 필요 (24.07.31 추가됨)
			EnhancedInputComponent->BindAction(InputData->Actions[11], ETriggerEvent::Completed, this, &ATestFPVPlayerController::BombSetCancel_Con);	// => 메인 수정 필요 (24.07.30 해당 키에 연동된 함수 변경됨)
			EnhancedInputComponent->BindAction(InputData->Actions[20], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::ChangePosture_Con, -1);	// => 메인 수정 필요 (24.07.30 해당 함수에 연동된 키 변경됨) ('0' -> 'X')
			EnhancedInputComponent->BindAction(InputData->Actions[13], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::CheckItem_Con);		// => 메인 수정 필요 (24.07.29 해당 키에 연동된 함수 변경됨) (PickUpItem -> CheckItem)
			EnhancedInputComponent->BindAction(InputData->Actions[14], ETriggerEvent::Triggered, this, &ATestFPVPlayerController::ChangePOV_Con);		// => 메인 수정 필요 (24.07.30 플레이어 함수와의 혼동을 방지하지 위해 이름 수정됨)
			EnhancedInputComponent->BindAction(InputData->Actions[15], ETriggerEvent::Started, this, &ATestFPVPlayerController::Crouch);
			EnhancedInputComponent->BindAction(InputData->Actions[16], ETriggerEvent::Started, this, &ATestFPVPlayerController::IAReload);
		}
	}
}

void ATestFPVPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void ATestFPVPlayerController::MouseRotation(const FInputActionValue& Value)
{
	FVector2D MouseXY = Value.Get<FVector2D>();
	AddYawInput(MouseXY.X);
	AddPitchInput(-MouseXY.Y);
}

void ATestFPVPlayerController::MoveFront(const FInputActionValue& Value)
{
	FVector Forward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(Forward);
	ChangePlayerDir(EPlayerMoveDir::Forward);
}

void ATestFPVPlayerController::MoveBack(const FInputActionValue& Value)
{
	FVector Backward = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(-Backward);
	ChangePlayerDir(EPlayerMoveDir::Back);
}

void ATestFPVPlayerController::MoveRight(const FInputActionValue& Value)
{
	FVector Rightward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(Rightward);
	ChangePlayerDir(EPlayerMoveDir::Right);
}

void ATestFPVPlayerController::MoveLeft(const FInputActionValue& Value)
{
	FVector Leftward = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(-Leftward);
	ChangePlayerDir(EPlayerMoveDir::Left);
}

void ATestFPVPlayerController::Crouch(const FInputActionValue& Value)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	Ch->CrouchCameraMove();
}

//void ATestFPVPlayerController::Jump(const FInputActionValue& Value)
//{
//	ChangeStateController(EPlayerState::Jump);
//	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	Ch->Jump();
//}
//
//void ATestFPVPlayerController::JumpEnd()
//{
//	ChangeStateController(EPlayerState::Idle);
//	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	Ch->StopJumping();
//}

void ATestFPVPlayerController::FireStart(float _DeltaTime)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	if (nullptr == Ch)
	{
		return;
	}
	Ch->AttackCheck();
	IsGunFire = true;
}

void ATestFPVPlayerController::FireTick(float _DeltaTime)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	if (nullptr == Ch)
	{
		return;
	}

	// 내가 총일때만
	if (true == IsGunFire || Ch->IdleDefault == EPlayerUpperState::Rifle_Idle)
	{
		Ch->AttackCheck();
	}

	// Camera(Controller) Shake
	float ShakeX = Stream.FRandRange(-0.2f, 0.2f);
	float ShakeY = Stream.FRandRange(0.0f, 0.2f);
	FRotator(ShakeX, ShakeY, 0.0f);

	//FRotator ShakeRotator = FRotator(FQuat::Slerp(Rotation1.ToQuat(), Rotation2.ToQuat(), Alpha));
	//SetControlRotation(ShakeRotator);

	MouseRotation(FInputActionValue(FVector2D(ShakeX, ShakeY)));
	
}

void ATestFPVPlayerController::FireEnd()
{
	IsGunFire = false;
//	GetWorld()->GetTimerManager().ClearTimer(MyTimeHandle);
//	
//	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	if (nullptr == Ch)
//	{
//		return;
//	}
//
//	Ch->AttackEndCheck();
//
//#ifdef WITH_EDITOR
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString(TEXT("Attack End")));
//#endif // WITH_EDITOR
}

void ATestFPVPlayerController::Drink_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->Drink();
}

void ATestFPVPlayerController::BombSetStart_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->BombSetStart();
}

void ATestFPVPlayerController::BombSetTick_Con()	// => 메인에 추후 이전해야 함 (24.07.31 추가 후 테스팅 중)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->BombSetTick();
}

void ATestFPVPlayerController::BombSetCancel_Con()	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중) => 메인 적용(주석)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->BombSetCancel();
}

void ATestFPVPlayerController::CheckItem_Con()	// => 메인으로 이전 필요 (24.07.29 추가됨) => 메인 적용
{
	// E Key
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->CheckItem();
}

void ATestFPVPlayerController::ChangePosture_Con(int _InputKey)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();

	if (_InputKey == 0) // 총
	{
		Ch->ChangeMontage(EPlayerUpperState::Rifle_Idle, true);
		//ChangePostureToWidget(0); // BP To Event 
		//ChangePostureToWidget(EPlayerUpperState::Rifle_Idle); // 아마?
	}
	else if (_InputKey == 1) // 칼
	{
		Ch->ChangeMontage(EPlayerUpperState::Melee_Idle, true);
		//ChangePostureToWidget(EPlayerPosture::Rifle2); // BP To Event
		//ChangePostureToWidget(EPlayerUpperState::Rifle_Idle);
	}
	else if (_InputKey == -1) // 주먹
	{
		Ch->ChangeMontage(EPlayerUpperState::UArm_Idle, true);
	}

	Ch->SettingItemSocket(_InputKey);
}

void ATestFPVPlayerController::ChangePOV_Con()
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->ChangePOV();
}

void ATestFPVPlayerController::IAReload()
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->CharacterReload();
}

// 캐릭터의 ChangeLowerState_Implementation을 사용하고 있으므로 여기서는 사용하지 않는 함수.
//void ATestFPVPlayerController::ChangeLowerState(EPlayerLowerState _State)
//{
//	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	Ch->ChangeLowerState(_State);
//}

void ATestFPVPlayerController::ChangePlayerDir(EPlayerMoveDir _Dir)
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->ChangePlayerDir(_Dir);
}

//void ATestFPVPlayerController::PlayerMontagePlay()
//{
//	// 메인 적용 필요
//	// 기절, 폭탄 설치 상태 몽타주 실행 불가능
//	if (PlayerIsFaint == true || PlayerIsBombSetting == true)
//	{
//		return;
//	}
//
//	//ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	//Ch->ChangeMontage(false);
//}

//void ATestFPVPlayerController::FireEndMontagePlay()
//{
//	// 메인 적용 필요
//	// 기절, 폭탄 설치 상태 몽타주 실행 불가능
//	if (PlayerIsFaint == true || PlayerIsBombSetting == true)
//	{
//		return;
//	}
//
//	//ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
//	//Ch->ChangeMontage(true);
//}

void ATestFPVPlayerController::SetFaint()
{
	ATestFPVCharacter* Ch = GetPawn<ATestFPVCharacter>();
	Ch->ChangeIsFaint();
}

FGenericTeamId ATestFPVPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void ATestFPVPlayerController::CallGetItem()
{
	CallGetItemToWidget();
}








/*
* ChangePOV (Client)
* ChangePosture
* ChangeMontage
* ChangeAnimation
* ChangeLowerState
* ChangePlayerDir
* ChangeIsFaint
*/

/*
* EPlayerUpperState -> Mon
* 
* EPlayerPosture -> Seq
* PlayerDir
* PlayerLowerState
*/
