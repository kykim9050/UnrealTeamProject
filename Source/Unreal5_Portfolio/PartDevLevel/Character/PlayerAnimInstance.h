// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UPlayerAnimInstance : public UMainAnimInstance
{
	GENERATED_BODY()

public:
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ATestCharacter* OwnerPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PlayerMesh = nullptr;
};
