// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "TestCharacter.generated.h"

// Inventory (for UI Test) => 메인캐릭터로 이전해야 함 (PickUpItem 함수에 필요)
USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName Name = "";

	// Bullet Count, Damage
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadMaxNum = -1;	// 총기류 무기 탄 최대 갯수
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ReloadLeftNum = -1;	// 총기류 무기 탄 현재 갯수
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Damage = 0;			// 무기 공격력

	// Static Mesh
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* MeshRes = nullptr;			// 스태틱 메시 리소스
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector RelLoc = FVector(0.0f, 0.0f, 0.0f);		// 스태틱 메시 컴포넌트 상대적 위치
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator RelRot = FRotator(0.0f, 0.0f, 0.0f);	// 스태틱 메시 컴포넌트 상대적 회전
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector RelScale = FVector(1.0f, 1.0f, 1.0f);	// 스태틱 메시 컴포넌트 상대적 크기
};

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
	UPROPERTY(Category = "Contents", VisibleDefaultsOnly)
	USkeletalMeshComponent* FPVMesh = nullptr;	// => 메인캐릭터로 이전해야 함 (새로 추가됨)
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RidingMesh = nullptr;	// => 메인캐릭터로 이전해야 함 (새로 추가됨) [뭐하는 Component?] [탈것 테스팅용 (성우님 요청)]
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemSocketMesh = nullptr;	// => 메인캐릭터로 이전해야 함 (새로 추가됨)
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FPVItemSocketMesh = nullptr;	// => 메인캐릭터로 이전해야 함 (새로 추가됨)
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTestMinimapIconComponent* MinimapIconComponent = nullptr;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UHeadNameWidgetComponent* HeadNameComponent = nullptr;	// => 메인으로 이전 필요 (24.07.30 추가됨)
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GetMapItemCollisonComponent = nullptr;

	// State, Posture
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerState StateValue = EPlayerState::Idle;
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PostureValue = EPlayerPosture::Barehand;

	// LowerState (태환)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState LowerStateValue = EPlayerLowerState::Idle;

	// UpperState
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerUpperState UpperStateValue = EPlayerUpperState::Rifle_Idle;

	// Dir
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir DirValue = EPlayerMoveDir::Forward;

	// 7/26 추가 기절상태
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFaint = false;

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

	// 7/26 기절상태로 변경하는 함수 (태환)
	UFUNCTION(Reliable, Server)
	void ChangeIsFaint();
	void ChangeIsFaint_Implementation();

	// POV	// => const 값들 메인캐릭터 이전 필요 (24.07.29 추가됨) => 메인 적용.
	const FVector CameraRelLoc = FVector(0.0f, 60.0f, 110.0f);
	const FVector FPVCameraRelLoc = FVector(0.0f, 0.0f, 72.0f);
	const FVector FPVCameraRelLoc_Crouch = FVector(10.0f, 0.0f, 10.0f);
	bool IsFPV = true;
	UFUNCTION()
	void ChangePOV();
	UFUNCTION()
	void CharacterReload();

	// Inventory => 메인캐릭터로 이전해야 함 (PickUpItem 함수에 필요)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemInformation> ItemSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> IsItemIn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurItemIndex = -1;

	// Item
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* GetMapItemData = nullptr;	// 맵에 있는 무기 Data
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString RayCastToItemName = "";
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision);
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapEnd();
	UFUNCTION(BlueprintCallable)
	void CheckItem();	// => 메인캐릭터로 이전해야 함 (24.07.29 추가됨)
	UFUNCTION(Reliable, Server)
	void InteractObject(AMapObjectBase* _MapObject);	// => 메인캐릭터로 이전해야 함 (24.07.29 추가됨)
	void InteractObject_Implementation(AMapObjectBase* _MapObject);
	UFUNCTION(Reliable, Server)
	void PickUpItem();
	void PickUpItem_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void DropItem();	// => 메인캐릭터로 이전해야 함 (24.07.29 수정됨)
	void DropItem_Implementation();
	UFUNCTION(BlueprintCallable)
	void DeleteItem(int _Index);	// => 메인캐릭터로 이전해야 함 (24.07.29 추가됨)

	// Collision
	//UFUNCTION(BlueprintCallable)
	//void Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// NotifyState에서 사용 중 (태환)
	UFUNCTION(BlueprintCallable)
	void HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// Notify에서 호출.
	void ChangeHandAttackCollisionProfile(FName _Name);

	// HP (for UI, Monster Test)
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetPlayerHp()
	{
		return PlayerHp;
	}

	UFUNCTION(BlueprintCallable)
	void GetDamage(float _Damage); // Player State로 이동.

	UFUNCTION()
	void SendTokenToHpBarWidget();

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHp(float _DeltaTime);

	UFUNCTION(Reliable, Server)
	void SettingPlayerState();
	void SettingPlayerState_Implementation();

protected:
	// 메인 플레이어 추가 필요 코드 (태환) 07/24
	void PostInitializeComponents() override;
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
	// 근접 공격에 사용 중 (태환)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HandAttackComponent = nullptr;

	// 몽타주 변경에 사용 중 (태환)
	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnimInst;
	UPROPERTY()
	class UPlayerAnimInstance* FPVPlayerAnimInst;


	//UPROPERTY()
	//float CurHp = 0.0f;

	UPROPERTY()
	float MyMaxHp = 0.0f;

public:
	// Fire
	UFUNCTION(Reliable, Server, BlueprintCallable)	// => 메인도 수정해야 함 (24.07.25 수정됨)
	void FireRayCast();
	void FireRayCast_Implementation();

	// Drink
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void Drink();	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)
	void Drink_Implementation();

	// Bomb Setting
	UPROPERTY(Replicated ,BlueprintReadWrite)
	bool IsBombSetting = false;	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetStart();	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)
	void BombSetStart_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetCancel();	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)
	void BombSetCancel_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetComplete();	// => 메인에 추후 이전해야 함 (24.07.29 추가 후 테스팅 중)
	void BombSetComplete_Implementation();

	// 공격 시 서버 캐릭터 몽타주 변경 함수 (태환)
	UFUNCTION(Reliable, Server)
	void ChangeMontage(bool _IsFireEnd);
	void ChangeMontage_Implementation(bool _IsFireEnd);

	// 공격 시 클라이언트 캐릭터 몽타주 변경 함수 (태환)
	UFUNCTION(Reliable, NetMulticast)
	void ClientChangeMontage(bool _IsFireEnd);
	void ClientChangeMontage_Implementation(bool _IsFireEnd);

	// Crouch 카메라 이동
	UFUNCTION()
	void CrouchCameraMove();

	UFUNCTION()
	void NetCheck();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsServer = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsClient = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsCanControlled = false;

	UPROPERTY(Category = "TPSNet", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Token = -1;
};