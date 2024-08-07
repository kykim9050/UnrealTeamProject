// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/MonsterBase.h"
#include "MainGameLevel/Monster/Base/BasicMonsterData.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Components/TimeLineComponent.h"
#include "BasicMonsterBase.generated.h"

class UCurveFloat;
class USphereComponent;
class UMaterialInstanceDynamic;
class UMonsterRandomAnimInstance;
class ABasicMonsterAIController;

UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterBase : public AMonsterBase
{
	GENERATED_BODY()

public:
	ABasicMonsterBase();

public:
	// Server Only
	void Damaged(float Damage) override;
	void SetChasePlayer();

public:
	// Get, Set
	FORCEINLINE ABasicMonsterAIController* GetAIController() const
	{
		return AIController;
	}

	FORCEINLINE UMonsterRandomAnimInstance* GetAnimInstance() const
	{
		return AnimInst;
	}

	FORCEINLINE USphereComponent* GetAttackComponent() const
	{
		return AttackComponent;
	}

	FORCEINLINE UBasicMonsterData* GetSettingData() const
	{
		return SettingData;
	}

	FORCEINLINE int GetAnimIndex()
	{
		return AnimIndex;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Data
	virtual void InitData(const FMonsterDataRow* BaseData) {};

	// Attack
	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Dead
	UFUNCTION(Reliable, NetMulticast)
	void SetDead();
	void SetDead_Implementation();

	UFUNCTION()
	void DeadDissolveInterp(float _Value);
	UFUNCTION()
	void DeadFinish()
	{
		Destroy();
	}

private:
	// Dissolve Effect
	UPROPERTY()
	FTimeline DeadTimeLine;

	UPROPERTY(EditAnywhere, Category = "DeadTimeLine")
	UCurveFloat* DeadDissolveCurve;

	FOnTimelineEvent DeadTimelineFinish;
	FOnTimelineFloat DeadDissolveCallBack;

	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

protected:
	UPROPERTY()
	UBasicMonsterData* SettingData = nullptr;

private:	
	// Data
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY()
	ABasicMonsterAIController* AIController = nullptr;

public:
	// 애니메이션
	template<typename EnumType>
	void ChangeRandomAnimation(EnumType Type)
	{
		ChangeRandomAnimation(static_cast<uint8>(Type));
	}

	void ChangeRandomAnimation(uint8 Type);

private:
	UPROPERTY(Replicated)
	uint8 AnimType = 0;

	UPROPERTY(Replicated)
	int AnimIndex = 0;

	UPROPERTY()
	UMonsterRandomAnimInstance* AnimInst = nullptr;

private:
	// 컴포넌트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USphereComponent* AttackComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* BloodParticle = nullptr;

};
