// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimeLineComponent.h"
#include "Global/DataTable/BossDataRow.h"

#include "TestBossMonsterBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ATestBossMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestBossMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//// 네트워크 동기화 프로퍼티
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	class ATestBossMonsterAIControllerBase* GetBossAIController();
	class UMainAnimInstance* GetAnimInstance();
	void FireProjectile();

	void ChangeAniValue(uint8 _Type);

	template<typename EnumType>
	void ChangeAniValue(EnumType _Type)
	{
		ChangeAniValue(static_cast<uint8>(_Type));
	}

	FORCEINLINE float GetMeleeAttackDamage()
	{
		return SettingBossData->Data->GetMeleeAttackDamage();
	}

	FORCEINLINE float GetRangedAttackDamage()
	{
		return SettingBossData->Data->GetRangedAttackDamage();
	}

	FORCEINLINE float GetBossMonsterHp()
	{
		return SettingBossData->HP;
	}

	void Damaged(float Damage);
	void SetAttackCollision(bool Active);

private:
	UFUNCTION(Reliable, NetMulticast)
	void SetOnDead();
	void SetOnDead_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void BossHP_HUDCheck();
	void BossHP_HUDCheck_Implementation();

	void OnDead();

	UFUNCTION()
	void SpawnReportObject();

protected:
	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual void MeleeAttack(AActor* _OtherActor, UPrimitiveComponent* _Collision);

private:
	UPROPERTY()
	UBossData* SettingBossData;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName BossDataName;

	UPROPERTY(Replicated)
	uint8 AniValue;

	UPROPERTY(Replicated)
	float Hp;
	float CurHp;

	UPROPERTY()
	class UMainAnimInstance* MainAnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USphereComponent* MeleeAttackComponent;

	UPROPERTY(EditAnywhere, Category = "Particle", meta = (AllowPrivateAccess = true))
	UParticleSystem* BloodParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABossProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FVector MuzzleOffset;



};
