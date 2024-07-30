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

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:

};
