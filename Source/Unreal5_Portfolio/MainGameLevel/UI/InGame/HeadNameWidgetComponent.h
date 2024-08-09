// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "HeadNameWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UHeadNameWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void InitWidget() override;

	UHeadNameWidgetComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void BilboardRotate(FVector _WorldLocation);

	UFUNCTION()
	void SetHeadNameRelativeLocation(FVector _Loc);

	UFUNCTION()
	void SetHeadNameRelativeRotation(FVector _Rot);

	UFUNCTION()
	void SetHeadNameWidgetText(FText _Name);

	UFUNCTION(Reliable, Server)
	void SendNicknames(const FText& _Nickname);
	void SendNicknames_Implementation(const FText& _Nickname);

	UPROPERTY(Replicated)
	FText HeadNameText;

	UPROPERTY()
	FTimerHandle HeadNameHandle;
private:
};
