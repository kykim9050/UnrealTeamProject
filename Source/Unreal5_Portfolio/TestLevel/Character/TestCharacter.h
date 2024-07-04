// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "TestCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

	// Components
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> ItemMeshes;

	// State, Posture
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerState StateValue = EPlayerState::Idle;
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PostureValue = EPlayerPosture::Barehand;

	UFUNCTION(Reliable, Server)
	void ChangeState(EPlayerState _Type);
	void ChangeState_Implementation(EPlayerState _Type);
	UFUNCTION(Reliable, Server)
	void ChangePosture(EPlayerPosture _Type);
	void ChangePosture_Implementation(EPlayerPosture _Type);

	// Item (for UI Test)
	struct FItemInfo
	{
		FName Name = "";
		int ReloadMaxNum = -1;
		int ReloadLeftNum = -1;
	};
	TArray<FItemInfo*> ItemSlot;
	TArray<bool> IsItemIn;
	FItemInfo* CurItem = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(FName _ItemName);

	UFUNCTION(Reliable, Server)
	void PickUpItem(FName _ItemName);
	void PickUpItem_Implementation(FName _ItemName);

	UFUNCTION(BlueprintCallable)
	inline bool GetPickUp()
	{
		return PickUp;
	}
	UFUNCTION(BlueprintCallable)
	inline void SetPickUp(bool _PickUp)
	{
		PickUp = _PickUp;
	}

	// Collision
	UFUNCTION(BlueprintCallable)
	void Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// HP (for UI Test)
	UFUNCTION(BlueprintCallable)
	inline float GetPlayerHp()
	{
		return PlayerHp;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Item
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PickUp = false;

	// HP (for UI Test)
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerHp = 100.0f;
};