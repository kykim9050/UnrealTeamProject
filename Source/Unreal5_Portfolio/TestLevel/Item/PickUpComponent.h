// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, class ATestCharacter*, PickUpCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPutDown, class ATestCharacter*, PutDownCharacter);

/**
 * 줍기, 버리기 컴포넌트
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL5_PORTFOLIO_API UPickUpComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPutDown OnPutDown;

	UPickUpComponent();

protected:
	void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void TriggerPickUpEvent(class ATestCharacter* PickUpCharacter);

	void TriggerPutDownEvent(class ATestCharacter* PutDownCharacter);

};
