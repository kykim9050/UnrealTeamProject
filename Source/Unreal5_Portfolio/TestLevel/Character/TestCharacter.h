// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "TestCharacter.generated.h"

// Inventory (for UI Test)
USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName Name = "";
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadMaxNum = -1;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadLeftNum = -1;
};

UCLASS()
class UNREAL5_PORTFOLIO_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();



	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AActor* CurItem = nullptr;



	// Components
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTestMinimapIconComponent* MinimapIconComponent = nullptr;
	//UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TArray<UStaticMeshComponent*> ItemMeshes;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	const class USkeletalMeshSocket* WeaponSocket = nullptr;

	// State, Posture
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerState StateValue = EPlayerState::Idle;
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PostureValue = EPlayerPosture::Barehand;

	// LowerState (태환)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState LowerStateValue = EPlayerLowerState::Idle;

	// Dir
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir DirValue = EPlayerMoveDir::Forward;

	UFUNCTION(Reliable, Server)
	void ChangeState(EPlayerState _Type);
	void ChangeState_Implementation(EPlayerState _Type);
	UFUNCTION(Reliable, Server)
	void ChangePosture(EPlayerPosture _Type);
	void ChangePosture_Implementation(EPlayerPosture _Type);

	// LowerStateChange 함수 (태환)
	UFUNCTION(Reliable, Server)
	void ChangeLowerState(EPlayerLowerState _LowerState);
	void ChangeLowerState_Implementation(EPlayerLowerState _LowerState);

	// DirChange 함수 (태환)
	UFUNCTION(Reliable, Server)
	void ChangePlayerDir(EPlayerMoveDir _Dir);
	void ChangePlayerDir_Implementation(EPlayerMoveDir _Dir);

	// Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemInformation> ItemSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> IsItemIn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurItemIndex = -1;
	
	// Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* GetMapItem = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString RayCastToItemName = "";
	UFUNCTION(Reliable, Server)
	void PickUpItem();
	void PickUpItem_Implementation();

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

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void CharacterPlayerToDropItem(FName _ItemName, FTransform _Transform);
	void CharacterPlayerToDropItem_Implementation(FName _ItemName, FTransform _Transform);

	// Collision
	UFUNCTION(BlueprintCallable)
	void Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	UFUNCTION(BlueprintCallable)
	void HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	void ChangeHandAttackCollisionProfile(FName _Name);

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HandAttackComponent = nullptr;

	// 몽타주 변경에 필요한 변수 (태환)
	UPROPERTY(Replicated)
	uint8 PlayerMontageAniValue;

	UPROPERTY(Replicated)
	class UMainAnimInstance* PlayerAnimInst;
	//

public:
	UFUNCTION(BlueprintCallable)
	void TestRayCast(float _DeltaTime, FVector _StartPos, FVector _EndPos, FRotator _CameraRot);

	UFUNCTION(BlueprintCallable)
	void DefaultRayCast(float _DeltaTime);

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void FireRayCast(float _DeltaTime);
	void FireRayCast_Implementation(float _DeltaTime);

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void ChangeMontage(EPlayerPosture _Posture);
	void ChangeMontage_Implementation(EPlayerPosture _Posture);
};