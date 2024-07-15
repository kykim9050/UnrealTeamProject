// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//void PostLogin(APlayerController* NewPlayer) override;

public:
	void CreateMonsterSpawner(FName _DataTableRowName);

private:
	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxMonsterNum = 0;

};
