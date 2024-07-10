// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Character.h"
#include "Components/TimeLineComponent.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "TestMonsterBase.generated.h"

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
	class UMainAnimInstance* GetAnimInstance();
	
	void ChangeAniValue(uint8 _Type);

	template<typename EnumType>
	void ChangeAniValue(EnumType _Type)
	{
		ChangeAniValue(static_cast<uint8>(_Type));
	}

	FORCEINLINE bool GetIsCharacterHit()
	{
		return IsCharacterHit;
	}

	FORCEINLINE void SetIsCharacterHit(bool IsHit)
	{
		IsCharacterHit = IsHit;
	}

	FORCEINLINE float GetAttackDamage()
	{
		return SettingData->AttackDamage;
	}

	FORCEINLINE float GetMonsterHp()
	{
		return SettingData->Hp;
	}

	void Damaged(float Damage);
	void SetActiveAttackCollision(bool Active);

protected:
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual void Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision);

private:
	UFUNCTION(Reliable, NetMulticast)
	void SetDeadCollision();
	void SetDeadCollision_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void SetDeadTimeline();
	void SetDeadTimeline_Implementation();

	void OnDead();
	UFUNCTION()
	void OnDeadDissolveInterp(float _Value);
	UFUNCTION()
	void OnDeadFinish()
	{
		Destroy();
	}

private:
	const FMonsterDataRow* BaseData;

	UPROPERTY()
	UMonsterData* SettingData;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY(Replicated)
	uint8 AniValue;

	UPROPERTY(Replicated)
	class UMainAnimInstance* AnimInst;

	TArray<class UMaterialInstanceDynamic*> DynamicMaterials;
	
	UPROPERTY()
	FTimeline DeadTimeLine;

	UPROPERTY(EditAnywhere, Category = "DeadTimeLine")
	class UCurveFloat* DeadDissolveCurve;
	
	FOnTimelineFloat DeadDissolveCallBack;
	FOnTimelineEvent DeadTimelineFinish;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UCapsuleComponent* LeftAttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UCapsuleComponent* RightAttackComponent;

	bool IsCharacterHit = false;
};
