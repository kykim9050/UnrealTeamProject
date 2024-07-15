// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
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


	void ChangeAniValue(uint8 _Type);

	template<typename EnumType>
	void ChangeAniValue(EnumType _Type)
	{
		ChangeAniValue(static_cast<uint8>(_Type));
	}

private:
	const FBossDataRow* BossData;

	UPROPERTY()
	UBossData* SettingBossData;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName BossDataName;

	UPROPERTY(Category = "Animation", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 AniValue;

	UPROPERTY(Category = "Animation", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMainAnimInstance* MainAnimInst;

};
