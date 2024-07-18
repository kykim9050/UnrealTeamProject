// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "BasicMonsterBase.generated.h"

class USphereComponent;
class UBasicMonsterAnimInstance;
class ABasicMonsterAIController;

UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABasicMonsterBase();

public:
	template<typename EnumType>
	void ChangeAniType(EnumType Type)
	{
		ChangeAniType(static_cast<uint8>(Type));
	}

	FORCEINLINE void ChangeAniType(uint8 Type)
	{
		AnimType = Type;
	}

	FORCEINLINE ABasicMonsterAIController* GetAIController() const
	{
		return AIController;
	}

	FORCEINLINE UBasicMonsterAnimInstance* GetAnimInstance() const
	{
		return AnimInst;
	}

	FORCEINLINE const FMonsterDataRow* GetBaseData() const
	{
		return SettingData->BaseData;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:	
	// Data
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY()
	UMonsterData* SettingData = nullptr;

	UPROPERTY()
	ABasicMonsterAIController* AIController = nullptr;

private:
	// 애니메이션
	UPROPERTY(Replicated)
	uint8 AnimType;

	UBasicMonsterAnimInstance* AnimInst = nullptr;

private:
	// 컴포넌트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USphereComponent* AttackComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* BloodParticle;
};
