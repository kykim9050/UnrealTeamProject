// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestTitleUI.generated.h"


struct FNetDataRow;

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTestTitleUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ServerStart();
	UFUNCTION(BlueprintCallable)
	void Connect(FString _IP);
	UFUNCTION(BlueprintCallable)
	void ServerTest(FName _IPName); // 나중에 방식 바꿀거임
	virtual bool Initialize() override;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

	FString IPAddress = TEXT("127.0.0.1");
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Port = TEXT("30001");

	const FNetDataRow* Test;

};
