// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimeLineComponent.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "BasicMonsterBase.generated.h"

class UCurveFloat;
class USphereComponent;
class UMaterialInstanceDynamic;
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

public:
	// Server Only
	void Damaged(float Damage);

	void SetAttackCollision(bool Active);

public:
	// Get / Set
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

	void Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision);
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
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

	UPROPERTY()
	UBasicMonsterAnimInstance* AnimInst = nullptr;

private:
	// 컴포넌트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USphereComponent* AttackComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* BloodParticle;

	// Dissolve
	UPROPERTY()
	FTimeline DeadTimeLine;

	UPROPERTY(EditAnywhere, Category = "DeadTimeLine")
	UCurveFloat* DeadDissolveCurve;

	FOnTimelineEvent DeadTimelineFinish;
	FOnTimelineFloat DeadDissolveCallBack;

	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

};
