// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Global/ContentsEnum.h"
#include "ParentsCharacter.h"
#include "TestFPVCharacter.generated.h"

// For Character Part's Testing : First person point of view 

// Inventory				// => 메인캐릭터로 이전해야 함
USTRUCT(BlueprintType)
struct FFPVItemInformation
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))	// => 메인 이전 필요 (24.08.06 추가됨)
	bool IsItemIn = false;	// 인벤토리 칸에 아이템이 들어 있는지 여부

	// ItemName
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
class UNREAL5_PORTFOLIO_API ATestFPVCharacter : public AParentsCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestFPVCharacter();

	// LowerState (태환)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState LowerStateValue = EPlayerLowerState::Idle;

	// Dir
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir DirValue = EPlayerMoveDir::Forward;

	// 7/26 추가 기절상태
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFaint = false;

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

	// POV
	const FVector CameraRelLoc = FVector(0.0f, 60.0f, 110.0f);			// => 메인캐릭터 이전 필요 (24.07.29 추가됨) => 메인 적용.
	const FVector FPVCameraRelLoc = FVector(10.0f, 0.0f, 72.0f);		// => 메인 수정 필요 (24.08.02 수정됨)
	const FVector FPVCameraRelLoc_Crouch = FVector(10.0f, 0.0f, 10.0f);	// => 메인캐릭터 이전 필요 (24.07.29 추가됨) => 메인 적용.
	//bool IsFPV = true;
	EPlayerFPSTPSState PointOfView = EPlayerFPSTPSState::FPS;
	UFUNCTION()
	void ChangePOV();
	UFUNCTION()
	void CharacterReload();

	// Inventory => 메인캐릭터로 이전해야 함 (PickUpItem 함수에 필요)
	UPROPERTY(/*Replicated, */VisibleAnywhere, BlueprintReadOnly)
	TArray<FFPVItemInformation> ItemSlot;							// => 메인 수정 필요 (24.08.06 수정됨)
	//UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)		// => 메인에서 삭제 필요 (24.08.06 삭제됨)
	//TArray<bool> IsItemIn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurItemIndex = -1;
	UFUNCTION()
	bool IsItemInItemSlot(int _Index);

	// Item
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* GetMapItemData = nullptr;	// 맵에 있는 무기 Data
	//UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//FString RayCastToItemName = "";
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	// => 메인 수정 필요 (24.08.01 수정됨)
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);	// => 메인 수정 필요 (24.08.01 수정됨)
	UFUNCTION(BlueprintCallable)
	void CheckItem();										// => 메인캐릭터로 이전해야 함 (24.07.29 추가됨)
	UFUNCTION(Reliable, Server)
	void InteractObject(AMapObjectBase* _MapObject);		// => 메인캐릭터로 이전해야 함 (24.07.29 추가됨)
	void InteractObject_Implementation(AMapObjectBase* _MapObject);
	UFUNCTION(/*Reliable, Server, */BlueprintCallable)
	void PickUpItem(AItemBase* _Item);						// => 메인 수정 필요 (24.08.06 수정됨)
	//void PickUpItem_Implementation(AItemBase* _Item);
	//UFUNCTION(BlueprintCallable)
	//void ItemSetting(FName _TagName, EPlayerUpperState _SlotIndex);	// => 메인 삭제 필요 (24.08.06 삭제됨)
	UFUNCTION(/*Reliable, Server, */BlueprintCallable)
	void DropItem(int _SlotIndex);							// => 메인 수정 필요 (24.08.06 수정됨)
	//void DropItem_Implementation(int _SlotIndex);
	UFUNCTION(Reliable, Server)
	void DestroyItem(AItemBase* _Item);						// => 메인 이전 필요 (24.08.06 추가됨)
	void DestroyItem_Implementation(AItemBase* _Item);
	UFUNCTION(Reliable, Server)
	void SpawnItem(FName _ItemName, FTransform _SpawnTrans);			// => 메인 이전 필요 (24.08.06 추가됨)
	void SpawnItem_Implementation(FName _ItemName, FTransform _SpawnTrans);
	UFUNCTION(BlueprintCallable)
	void DeleteItemInfo(int _Index);						// => 메인 수정 필요 (24.08.06 함수 이름 수정됨)

	// Collision
	//UFUNCTION(BlueprintCallable)
	//void Collision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// NotifyState에서 사용 중 (태환)
	UFUNCTION(BlueprintCallable)
	void HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	UFUNCTION()
	void SendTokenToHpBarWidget();

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHp(float _DeltaTime);

	UFUNCTION(Reliable, Server)
	void SettingPlayerState();
	void SettingPlayerState_Implementation();

	UFUNCTION(BlueprintCallable)
	void ShowMuzzle();

protected:
	// 메인 플레이어 추가 필요 코드 (태환) 07/24
	void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AnimationEnd() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	// 몽타주 변경에 사용 중 (태환)
	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnimInst = nullptr;
	UPROPERTY()
	class UPlayerAnimInstance* FPVPlayerAnimInst = nullptr;

public:
	// Fire
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void FireRayCast();
	void FireRayCast_Implementation();

	// Drink
	UFUNCTION(BlueprintCallable)
	void Drink();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void DrinkComplete();
	void DrinkComplete_Implementation();

	void ChangeHandAttackCollisionProfile(FName _Name);

	// Bomb Setting
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool IsBombSetting = false;	// => 메인에 이전 필요 (24.07.29 추가됨)
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetStart();		// => 메인에 이전 필요 (24.07.31 수정됨)
	void BombSetStart_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetTick();			// => 메인에 이전 필요 (24.07.31 수정됨)
	void BombSetTick_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetCancel();		// => 메인에 이전 필요 (24.07.31 수정됨)
	void BombSetCancel_Implementation();
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void BombSetComplete();		// => 메인에 이전 필요 (24.07.31 수정됨)
	void BombSetComplete_Implementation();

	// Animation, Montage
	UFUNCTION(Reliable, Server)				// 공격 시 서버 캐릭터 몽타주 변경 함수 (태환)
	void ChangeMontage(EPlayerUpperState _UpperState, bool IsSet = false);
	void ChangeMontage_Implementation(EPlayerUpperState _UpperState, bool IsSet = false);
	UFUNCTION(Reliable, NetMulticast)		// 공격 시 서버 캐릭터 몽타주 변경 함수 (태환)
	void ClientChangeMontage(EPlayerUpperState _UpperState);
	void ClientChangeMontage_Implementation(EPlayerUpperState _UpperState);

	UFUNCTION(/*Reliable, Server*/)
	void SettingItemSocket(int _InputKey);	// => 메인에 이전 필요 (24.08.06 추가됨)
	//void SettingItemSocket_Implementation(int _InputKey);
	UFUNCTION(Reliable, Server)
	void SetItemSocketMesh(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale);
	void SetItemSocketMesh_Implementation(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale);
	UFUNCTION(Reliable, Server)
	void SetItemSocketVisibility(bool _Visibility);
	void SetItemSocketVisibility_Implementation(bool _Visibility);

	UFUNCTION()
	void ItemToCheckAnimation();

	// Crouch 카메라 이동
	UFUNCTION()
	void CrouchCameraMove();

	UFUNCTION()
	void AttackCheck();

	UFUNCTION()
	void AttackEndCheck();

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

	UPROPERTY(Category = "TPSNet", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerUpperState IdleDefault = EPlayerUpperState::UArm_Idle;
};
