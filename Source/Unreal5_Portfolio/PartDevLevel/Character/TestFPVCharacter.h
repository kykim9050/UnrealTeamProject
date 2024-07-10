// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "TestFPVCharacter.generated.h"

// For Character Part's Testing : First person point of view 

UCLASS()
class UNREAL5_PORTFOLIO_API ATestFPVCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestFPVCharacter();

	// Components
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(Category = "Contents", VisibleDefaultsOnly)
	USkeletalMeshComponent* FPVMesh = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> ItemMeshes;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> FPVItemMeshes;

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
	UFUNCTION(Reliable, Server)
	void SettingItemMesh(int _ItemIndex);
	void SettingItemMesh_Implementation(int _ItemIndex);

	// POV
	bool IsFPV = true;

	UFUNCTION()
	void ChangePOV();

	// Inventory (for UI Test)
	struct FItemInfo
	{
		FName Name = "";
		int ReloadMaxNum = -1;
		int ReloadLeftNum = -1;
	};
	TArray<FItemInfo> ItemSlot;
	UPROPERTY()
	TArray<bool> IsItemIn;
	UPROPERTY()
	int CurItemIndex = -1;

	// Item
	UFUNCTION(Reliable, Server)
	void PickUpItem(FName _ItemName);
	void PickUpItem_Implementation(FName _ItemName);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetPickUp()
	{
		return PickUp;
	}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPickUp(bool _PickUp)
	{
		PickUp = _PickUp;
	}

	// Collision
	UFUNCTION(BlueprintCallable)
	void Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// HP (for UI, Monster Test)
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetPlayerHp()
	{
		return PlayerHp;
	}

	UFUNCTION(BlueprintCallable)
	void GetDamage(float _Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Item
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PickUp = false;

	// HP (for UI, Monster Test)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float PlayerHp = 100.0f;

public:	
	UFUNCTION(BlueprintCallable)
	void CreateRayCast();
};
