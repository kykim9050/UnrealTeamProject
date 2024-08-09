// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API ATriggerBoxBase : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATriggerBoxBase();

protected:
    virtual void BeginPlay() override;

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // 오버랩 시작 시 호출되는 함수
    UFUNCTION()
    void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

    // 모든 플레이어 위치 설정
    UFUNCTION(Reliable, NetMulticast)
    void SetAllPlayersLocation(const FVector& NewLocation);
    void SetAllPlayersLocation_Implementation(const FVector& NewLocation);

    // 시네마틱 시퀸스 재생
    UFUNCTION(Reliable, NetMulticast)
    void PlayCinematicSequence();
    void PlayCinematicSequence_Implementation();

    // 시네마틱 시퀸스 종료 확인
    UFUNCTION()
    void OnSequenceFinished();
    
    // 플레이어 조작 비활성화
    UFUNCTION(Reliable, NetMulticast)
    void DisablePlayerInput(APlayerController* PlayerController);
    void DisablePlayerInput_Implementation(APlayerController* PlayerController);

    // 플레이어 조작 활성화
    UFUNCTION(Reliable, NetMulticast)
    void EnablePlayerInput(APlayerController* PlayerController);
    void EnablePlayerInput_Implementation(APlayerController* PlayerController);

    // PlayerUI ON
    UFUNCTION(Reliable, NetMulticast)
    void EnablePlayerHUD(APlayerController* PlayerController);
    void EnablePlayerHUD_Implementation(APlayerController* PlayerController);

    // PlayerUI OFF
    UFUNCTION(Reliable, NetMulticast)
    void DisablePlayerHUD(APlayerController* PlayerController);
    void DisablePlayerHUD_Implementation(APlayerController* PlayerController);

    // BackGroundSound On/Off
    // _Value : true(Sound On), false(Sound Off)
    UFUNCTION(Reliable, NetMulticast)
    void BackgroundSoundOnOff(AGameState* _CurGameState, bool _Value);
    void BackgroundSoundOnOff_Implementation(AGameState* _CurGameState, bool _Value);

protected:
    UPROPERTY(Replicated)
    FVector CenterLocation;

    // 시네마틱 시퀀스 에셋
    UPROPERTY(Replicated, EditAnywhere, Category = "Cinematics")
    class ULevelSequence* LevelSequenceAsset;

    UPROPERTY(Replicated)
    bool IsPlayerTP = false;

};
