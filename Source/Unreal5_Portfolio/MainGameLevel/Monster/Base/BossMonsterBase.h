// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Monster/Base/MonsterBase.h"
#include "Components/TimeLineComponent.h"
#include "BossMonsterBase.generated.h"

class UCurveFloat;
class USphereComponent;
class UBossMonsterData;
class UMainAnimInstance;
class UMaterialInstanceDynamic;
class ABossMonsterAIController;
struct FBossMonsterDataRow;

UCLASS()
class UNREAL5_PORTFOLIO_API ABossMonsterBase : public AMonsterBase
{
	GENERATED_BODY()

public:
	ABossMonsterBase();

public:
	// Get,  Set
	FORCEINLINE ABossMonsterAIController* GetAIController() const
	{
		return AIController;
	}

	FORCEINLINE UMainAnimInstance* GetAnimInstance() const
	{
		return AnimInst;
	}

	FORCEINLINE UBossMonsterData* GetSettingData() const
	{
		return SettingData;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Data
	virtual void InitData(const FBossMonsterDataRow* BaseData) {};

private:
	// Dissolve Effect
	UPROPERTY()
	FTimeline DeadTimeLine;

	UPROPERTY(EditAnywhere, Category = "DeadTimeLine")
	UCurveFloat* DeadDissolveCurve;

	FOnTimelineFloat DeadDissolveCallBack;
	FOnTimelineEvent DeadTimelineFinish;

	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

protected:
	UPROPERTY()
	UBossMonsterData* SettingData = nullptr;

private:
	// Data
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY()
	ABossMonsterAIController* AIController = nullptr;

public:
	// 애니메이션
	void ChangeAnimation(uint8 Type);

	template<typename EnumType>
	void ChangeAnimation(EnumType Type)
	{
		ChangeAnimation(static_cast<uint8>(Type));
	}

private:
	UPROPERTY(Replicated)
	uint8 AnimType = 0;

	UPROPERTY()
	UMainAnimInstance* AnimInst = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USphereComponent* AttackComponent;

};
