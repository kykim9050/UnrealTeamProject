 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Character.h"
#include "Components/TimeLineComponent.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "TestMonsterBase.generated.h"

class USphereComponent;

UCLASS()
class UNREAL5_PORTFOLIO_API ATestMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	class ATestMonsterBaseAIController* GetAIController();
	class UMonsterAnimInstance* GetAnimInstance();
	
	template<typename EnumType>
	void ChangeRandomAnimation(EnumType _Type)
	{
		ChangeRandomAnimation(static_cast<uint8>(_Type));
	}

	void ChangeRandomAnimation(uint8 _Type);

	FORCEINLINE float GetAttackDamage()
	{
		return SettingData->AttackDamage;
	}

	FORCEINLINE float GetMonsterHp()
	{
		return SettingData->Hp;
	}

	FORCEINLINE int GetAniIndex()
	{
		return AniIndex;
	}

	FORCEINLINE const FMonsterDataRow* GetBaseData() const
	{
		return SettingData->BaseData;
	}

	void Damaged(float Damage);
	void SetAttackCollision(bool Active);
	void SetChasePlayer();

	class UMotionWarpingComponent* GetMotionWarpingComponent();

	void SpawnRock();

protected:
	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual void Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision);

private:
	UFUNCTION(Reliable, NetMulticast)
	void SetOnDead();
	void SetOnDead_Implementation();

	void OnDead();
	UFUNCTION()
	void OnDeadDissolveInterp(float _Value);
	UFUNCTION()
	void OnDeadFinish()
	{
		Destroy();
	}

private:
	UPROPERTY()
	UTestMonsterData* SettingData;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY()
	class ATestMonsterBaseAIController* AIController = nullptr;

	UPROPERTY()
	class UMonsterAnimInstance* AnimInst = nullptr;

	UPROPERTY(Replicated)
	uint8 AniType;

	UPROPERTY(Replicated)
	int AniIndex;

	TArray<class UMaterialInstanceDynamic*> DynamicMaterials;
	
	UPROPERTY()
	FTimeline DeadTimeLine;

	UPROPERTY(EditAnywhere, Category = "DeadTimeLine")
	class UCurveFloat* DeadDissolveCurve;
	
	FOnTimelineFloat DeadDissolveCallBack;
	FOnTimelineEvent DeadTimelineFinish;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USphereComponent* AttackComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* BloodParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMotionWarpingComponent> MotionWarpComponent;
};
