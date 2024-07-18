// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "DoorObject.generated.h"



UENUM(BlueprintType)
enum class EDoorType : uint8
{
	None,
	Silding		UMETA(DisplayName = "Sliding"),		
	Rotating	UMETA(DisplayName = "Rotating"),	
};



UCLASS()
class UNREAL5_PORTFOLIO_API ADoorObject : public AMapObjectBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMesh(FName _ObjName);

	UFUNCTION()
	void Sliding(float _DeltaTime);

	UFUNCTION()
	void Rotating(float _DeltaTime);

	UFUNCTION()
	void InterAction() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDoorType(EDoorType _Type)
	{
		Type = _Type;
	}

protected:
	ADoorObject();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	float MoveAmount = 0.f;
	bool SlideDoorOpen = false;
	bool RotateDoorOpen = false;

private:
	UPROPERTY()
	EDoorType Type = EDoorType::None;


};
