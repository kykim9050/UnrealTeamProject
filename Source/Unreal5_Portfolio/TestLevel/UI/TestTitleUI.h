// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestTitleUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UTestTitleUI : public UUserWidget
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, Category = "MyBtnEvent")
	//int MyBtnHover();
	//UFUNCTION(BlueprintCallable, Category = "MyBtnEvent")
	//int MyBtnUnhover();

	//UFUNCTION(BlueprintCallable)
	//void ServerStart();
	//UFUNCTION(BlueprintCallable)
	//void Connect(FString _IP);
	virtual bool Initialize() override;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString IPAddress = TEXT("127.0.0.1");
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Port = TEXT("30002");

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	bool IsHoverOnOff;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	EBtnType HoverBtnType;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
//	EBtnType UnHoverBtnType;
};
