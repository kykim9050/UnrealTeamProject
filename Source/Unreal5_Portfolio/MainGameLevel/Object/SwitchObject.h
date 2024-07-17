// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "SwitchObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ASwitchObject : public AMapObjectBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	FORCEINLINE void SetSwitchValue(bool _Value)
	{
		SwitchValue = _Value;
	}

protected:
	ASwitchObject();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UObject> InteractObjClass = TSubclassOf<UObject>();

	UPROPERTY()
	bool SwitchValue = false;

	UPROPERTY()
	FVector CollisionOffset = FVector(0.0f, 60.0f, 0.0f);
};
