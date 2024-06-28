// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Character.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class ATestMonsterBaseAIController* GetAIController();

private:
	const FMonsterDataRow* BaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName BaseDataName;

	UPROPERTY()
	UMonsterData* SettingData;

};
