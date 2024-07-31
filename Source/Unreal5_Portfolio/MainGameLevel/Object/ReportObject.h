// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "ReportObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API AReportObject : public AMapObjectBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCollisionOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
 
};
