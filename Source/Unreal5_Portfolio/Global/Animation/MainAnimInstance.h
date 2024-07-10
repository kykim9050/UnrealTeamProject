// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeBeginPlay() override;

	template<typename EnumType>
	void ChangeAnimation(EnumType _Key)
	{
		ChangeAnimation(static_cast<uint8>(_Key));
	}

	void ChangeAnimation(uint8 _Key);

	template<typename EnumType>
	void PushAnimation(EnumType _Key, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<uint8>(_Key), _Montage);
	}

	void PushAnimation(uint8 _Key, class UAnimMontage* _Montage);

	TMap<uint8, class UAnimMontage*> GetAnimMontages()
	{
		return AnimMontages;
	}

	UAnimMontage* GetKeyAnimMontage(uint8 Key)
	{
		return AnimMontages[Key];
	}

	class ATestCharacter* OwnerPlayer = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, class UAnimMontage*> AnimMontages;
};
