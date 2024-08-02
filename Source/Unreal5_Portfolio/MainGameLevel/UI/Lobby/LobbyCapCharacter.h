// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LobbyCapCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ALobbyCapCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCapCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetMyNumber(int _Num);

	UFUNCTION(BlueprintCallable)
	void SetMyMesh();

	UFUNCTION(BlueprintCallable)
	bool IsMyOrderCharacter();

private:
	UPROPERTY()
	int MyNumber = -1; // 자기가 몇번 플레이어의 마네킹인지 
};
