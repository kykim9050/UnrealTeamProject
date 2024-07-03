// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestLevel/Item/WeaponBase.h"
#include "RangedWP.generated.h"

/**
 * 원거리 무기 객체
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ARangedWP : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARangedWP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 원거리 무기 획득
	virtual void HandlePickUp(class ATestCharacter* PickUpCharacter) override;

	// 원거리 무기 버리기
	virtual void HandlePutDown(class ATestCharacter* PutDownCharacter) override;

};
