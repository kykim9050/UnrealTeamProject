// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/ContentsEnum.h"
#include "Net/UnrealNetwork.h"
#include "PartDevLevel/Character/ParentsCharacter.h"
#include "MainCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMainCharacter : public AParentsCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	/// <summary>
	/// Component 초기화 이후 호출.
	/// </summary>
	void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void AnimationEnd() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// AnimInstance
public :
	// 하체 정보 (Controller 에서 호출함. -> 나중에 수정 필요.)
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState LowerStateValue = EPlayerLowerState::Idle;

	// 상체 정보
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerUpperState UpperStateValue = EPlayerUpperState::UArm_Idle;
		
	// 캐릭터 방향 정보
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir DirValue = EPlayerMoveDir::Forward;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerUpperState IdleDefault = EPlayerUpperState::UArm_Idle;

	// 캐릭터 기절 여부.
	UPROPERTY(Category = "Contents"/*, Replicated*/, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFaint = false;

private : // 문제 발생 여지 있음 발생하면 그냥 지워야 함.
	// == Components ==
	
	// 스프링암
	// 카메라
	// 일인칭 메시
	// 미니맵 아이콘
	// 맵에 있는 아이템 탐색 전용 콜리전
	// 아이템 장착 소켓
	// 1인칭 아이템 장착 소켓
	// 근접 공격에 사용

		
	// == 인칭 변경 변수 ==
	UPROPERTY()
	EPlayerFPSTPSState PointOfView = EPlayerFPSTPSState::FPS;

	// == Inventory ==
	// 아이템 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<bool> IsItemIn;
	// 현재 아이템 정보.
	UPROPERTY(VisibleAnywhere)
	TArray<struct FPlayerItemInformation> ItemSlot;
	// 현재 아이템 Index
	UPROPERTY(VisibleAnywhere)
	int CurItemIndex = -1;

	// 폭탄 설치 진행 상황
	UPROPERTY()
	bool IsBombSetting = false;


	// 맵에 있는 무기 Data
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* GetMapItemData = nullptr;

	// 상체 정보
	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnimInst = nullptr;
	UPROPERTY()
	class UPlayerAnimInstance* FPVPlayerAnimInst = nullptr;
	
	UPROPERTY(Replicated)
	FName UIToSelectCharacter = "";

	// == Server ==
public :
	// 하제 변경
	UFUNCTION(Reliable, Server)
	void ChangeLowerState(EPlayerLowerState _LowerState);
	void ChangeLowerState_Implementation(EPlayerLowerState _LowerState);

	// 캐릭터 방향
	UFUNCTION(Reliable, Server)
	void ChangePlayerDir(EPlayerMoveDir _Dir);
	void ChangePlayerDir_Implementation(EPlayerMoveDir _Dir);

	// Fire Ray Cast
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void FireRayCast();
	void FireRayCast_Implementation();

	UFUNCTION(Reliable, Server)
	void ChangeMontage(EPlayerUpperState _UpperState, bool IsSet = false);
	void ChangeMontage_Implementation(EPlayerUpperState _UpperState, bool IsSet = false);

	UFUNCTION(Reliable, NetMulticast)
	void ClientChangeMontage(EPlayerUpperState _UpperState);
	void ClientChangeMontage_Implementation(EPlayerUpperState _UpperState);

	UFUNCTION(Reliable, Server)
	void SettingPlayerState();
	void SettingPlayerState_Implementation();

	UFUNCTION(Reliable, Server)
	void ChangeIsFaint();
	void ChangeIsFaint_Implementation();

	UFUNCTION(Reliable, Server)
	void InteractObject(AMapObjectBase* _MapObject);
	void InteractObject_Implementation(AMapObjectBase* _MapObject);

	UFUNCTION(Reliable, Server)
	void BombSetStart();
	void BombSetStart_Implementation();
	UFUNCTION(Reliable, Server)
	void BombSetTick();
	void BombSetTick_Implementation();
	UFUNCTION(Reliable, Server)
	void BombSetCancel();
	void BombSetCancel_Implementation();
	UFUNCTION(Reliable, Server)
	void BombSetEnd();
	void BombSetEnd_Implementation();

	/// <summary>
	/// Crouch 에 대한 카메라 이동
	/// </summary>
	UFUNCTION()
	void CrouchCameraMove();

	// == Client ==
private :
	const FVector CameraRelLoc = FVector(0.0f, 60.0f, 110.0f);
	const FVector FPVCameraRelLoc = FVector(0.0f, 0.0f, 72.0f);
	const FVector FPVCameraRelLoc_Crouch = FVector(10.0f, 0.0f, 10.0f);

	UFUNCTION(BlueprintCallable)
	void MapItemOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHp(float _DeltaTime);

	UFUNCTION(BlueprintCallable)
	void DeleteItem(int _Index);

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void GetSetSelectCharacter(class UMainGameInstance* _MainGameInstance);
	void GetSetSelectCharacter_Implementation(class UMainGameInstance* _MainGameInstance);

	UFUNCTION(Reliable, Server)
	void DestroyItem(AItemBase* _Item);
	void DestroyItem_Implementation(AItemBase* _Item);

	UFUNCTION(Reliable, Server)
	void SetItemSocketVisibility(bool _Visibility);
	void SetItemSocketVisibility_Implementation(bool _Visibility);

	UFUNCTION(Reliable, Server)
	void SetItemSocketMesh(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale);
	void SetItemSocketMesh_Implementation(UStaticMesh* _ItemMeshRes, FVector _ItemRelLoc, FRotator _ItemRelRot, FVector _ItemRelScale);

	UFUNCTION(Reliable, Server)
	void SpawnItem(FName _ItemName, FTransform _SpawnTrans);
	void SpawnItem_Implementation(FName _ItemName, FTransform _SpawnTrans);

	// 아이템 변경
	UFUNCTION(BlueprintCallable)
	void PickUpItem(class AItemBase* _Item);

	// 아이템 생성 -> 드랍
	UFUNCTION(BlueprintCallable)
	void DropItem(int _SlotIndex);

	UFUNCTION()
	void DeleteItemInfo(int _Index);

	UFUNCTION()
	bool IsItemInItemSlot(int _Index);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsServer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsClient = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsCanControlled = false;

	UPROPERTY(Category = "PlayerNet", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Token = -1;

	// == Client ==
public :
	UFUNCTION(BlueprintCallable)
	void CheckItem();

	UFUNCTION()
	void AttackCheck();

	UFUNCTION()
	void Drink();

	// 소켓에 아이템 설정.
	UFUNCTION()
	void SettingItemSocket(int _InputKey);

	UFUNCTION()
	FORCEINLINE EPlayerUpperState GetIdleDefault() const
	{
		return IdleDefault;
	}

public :
	// == 인칭 변경 함수 ==
	UFUNCTION()
	void ChangePOV();

	// 리로드.
	UFUNCTION()
	void CharacterReload();

	UFUNCTION(BlueprintCallable)
	void HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	UFUNCTION()
	void NetCheck();

	UFUNCTION()
	void SendTokenToHpBarWidget();

	// 캐릭터 장비(인벤토리) 정보.
	UFUNCTION(BlueprintCallable)
	TArray<struct FPlayerItemInformation> GetItemSlot();

protected :
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UGetItem_UserWidget* Reload_Widget = nullptr;
};

/** BP
* MovementComponent -> WalkableFloorAngle 의 값을 60.0으로 수정.
* 캡슐 콜리전 Player로 변경.
*/