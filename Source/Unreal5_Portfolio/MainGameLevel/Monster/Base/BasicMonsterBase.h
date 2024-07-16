// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "BasicMonsterBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ABasicMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABasicMonsterBase();

public:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
	// 기본 설정 데이터 (데이터 테이블 기반)
	const FMonsterDataRow* BaseData;
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;
	
	// 개별 설정 데이터
	UPROPERTY()
	UMonsterData* SettingData = nullptr;
	
private:
	// 애니메이션
	UPROPERTY(Replicated)
	uint8 AniValue;
	class UBasicMonsterAnimInstance* AnimInst = nullptr;

private:
	// 컴포넌트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	class USphereComponent* AttackComponent;


};
