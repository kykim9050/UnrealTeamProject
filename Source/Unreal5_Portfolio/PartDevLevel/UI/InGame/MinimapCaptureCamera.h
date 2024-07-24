// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/ContentsEnum.h"
#include "MinimapCaptureCamera.generated.h"

class ATestCharacter;
UCLASS()
class UNREAL5_PORTFOLIO_API AMinimapCaptureCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinimapCaptureCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetCharacter(ATestCharacter* _MyCharacter);

	UFUNCTION(BlueprintCallable)
	void FollowCharacter();

	UFUNCTION(BlueprintCallable)
	void SetSceneCameraType(EUserWidgetType _Type);
private:
	UPROPERTY()
	ATestCharacter* MyCharacter = nullptr;

	UPROPERTY()
	EUserWidgetType SceneCameraType = EUserWidgetType::WorldMap; // MiniMap인지 WorldMap인지 (Default - WorldMap)
};