// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Character/PlayerAnimInstance.h"
#include "TestLevel/Character/TestCharacter.h"
#include "MainGameLevel/Player/MainCharacter.h"
#include "PartDevLevel/Character/TestFPVCharacter.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerPlayer = Cast<ATestCharacter>(GetOwningActor());
	//OwnerPlayer = Cast<AMainCharacter>(GetOwningActor()); // Main - kjb
	//OwnerPlayer = Cast<ATestFPVCharacter>(GetOwningActor());

	// MainGameInst의 PlayerData에 저장된 Montages를 PlayerUpperMontages로 Add
	MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	TMap<EPlayerUpperState, class UAnimMontage*> PlayerUpperMontages = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetAnimMontages();
	for (TPair<EPlayerUpperState, class UAnimMontage*> Montage : PlayerUpperMontages)
	{
		PushAnimation(Montage.Key, Montage.Value);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (nullptr == OwnerPlayer)
	{
		return;
	}

	//PlayerPosture = OwnerPlayer->PostureValue;
	PlayerLowerState = OwnerPlayer->LowerStateValue;
	PlayerUppperState = OwnerPlayer->IdleDefault;
	PlayerDir = OwnerPlayer->DirValue;
	//PlayerIsFaint = OwnerPlayer->IsFaint;
	//PlayerIsBombSetting = OwnerPlayer->IsBombSetting;
}

void UPlayerAnimInstance::ChangeAnimation(EPlayerUpperState _UpperState)
{
	Super::ChangeAnimation(_UpperState);
}

void UPlayerAnimInstance::SetAnimMontages(TMap<EPlayerUpperState, class UAnimMontage*> _Montages)
{
	for (TPair<EPlayerUpperState, class UAnimMontage*> Montage : _Montages)
	{
		SetKeyAnimMontage(static_cast<uint8>(Montage.Key), Montage.Value);
	}

	GetAnimMontages();
}