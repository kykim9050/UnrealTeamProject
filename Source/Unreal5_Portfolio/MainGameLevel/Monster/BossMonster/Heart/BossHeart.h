// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BossMonsterBase.h"
#include "BossHeart.generated.h"

class UBossHeartData;
class ABossHeartProjectile;
struct FBossMonsterDataRow;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABossHeart : public ABossMonsterBase
{
	GENERATED_BODY()

public:
	ABossHeart();

public:
	UBossHeartData* GetSettingData() const
	{
		return BossHeartSettingData;
	}

public:
	void Shooting();
	
protected:
	virtual void InitData(const FBossMonsterDataRow* BaseData) override;
	virtual void DropItem() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBossHeartData* BossHeartSettingData = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABossHeartProjectile> ProjectileUClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FVector GunOffset = FVector::ZeroVector;

};
