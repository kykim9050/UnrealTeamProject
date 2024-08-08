// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/BossMonsterBase.h"
#include "BossKraken.generated.h"

class UBoxComponent;
class UBossKrakenData;
class ABossKrakenProjectile;
class UBossKrakenProjectileSpawnPoint;
struct FBossMonsterDataRow;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ABossKraken : public ABossMonsterBase
{
	GENERATED_BODY()

public:
	ABossKraken();

public:
	UBossKrakenData* GetSettingData() const
	{
		return BossKrakenSettingData;
	}

public:
	void SpawnRock();

protected:
	virtual void InitData(const FBossMonsterDataRow* BaseData) override;
	
private:
	UPROPERTY()
	UBossKrakenData* BossKrakenSettingData = nullptr;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent* BodyComponent = nullptr;

private:
	// Projectile
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	UBossKrakenProjectileSpawnPoint* ProjectileSpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABossKrakenProjectile> ProjectileUClass = nullptr;

};
