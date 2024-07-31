// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "LobbyCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ALobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Reliable, Server)
	void ClientReady();
	void ClientReady_Implementation();

	UPROPERTY()
	bool ReadyClicked = false;

private:
	UPROPERTY()
	AGameModeBase* IsServerPtr = nullptr; // nullptr¿Ã∏È client
};
