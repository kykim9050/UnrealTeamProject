// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/ContentsEnum.h"
#include "Net/UnrealNetwork.h"
#include "MainCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	
	// 플레이어 자세 유형
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PostureValue = EPlayerPosture::Barehand;
	
	// 캐릭터 방향 정보
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerMoveDir DirValue = EPlayerMoveDir::Forward;

private : // 문제 발생 여지 있음 발생하면 그냥 지워야 함.
	// == Components ==
	
	// 스프링암
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;
	// 카메라
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	// 일인칭 메시
	UPROPERTY(Category = "Contents", VisibleDefaultsOnly)
	USkeletalMeshComponent* FPVMesh = nullptr;
	// 탈 것?
	//UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UStaticMeshComponent* RidingMesh = nullptr;
	// 미니맵 아이콘
	//UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UTestMinimapIconComponent* MinimapIconComponent = nullptr;
	// 맵에 있는 아이템 탐색 전용 콜리전
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GetMapItemCollisonComponent = nullptr;
	// 버리는 아이템 생성 위치
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CreateItemComponent = nullptr;

	// 아이템 장착 소켓
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemSocketMesh = nullptr;
	// 1인칭 아이템 장착 소켓
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FPVItemSocketMesh = nullptr;	// => 메인캐릭터로 이전해야 함 (새로 추가됨)

		
	// == 인칭 변경 변수 ==
	UPROPERTY()
	bool IsFPV = true;

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


	// 맵에 있는 무기 Data
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* GetMapItemData = nullptr;

	// 상체 정보
	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnimInst;
	UPROPERTY()
	class UPlayerAnimInstance* FPVPlayerAnimInst;

	// 근접 공격에 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HandAttackComponent = nullptr;


	// == Server ==
public :
	// 상채 변경
	UFUNCTION(Reliable, Server)
	void ChangePosture(EPlayerPosture _Type);
	void ChangePosture_Implementation(EPlayerPosture _Type);

	// 하제 변경
	UFUNCTION(Reliable, Server)
	void ChangeLowerState(EPlayerLowerState _LowerState);
	void ChangeLowerState_Implementation(EPlayerLowerState _LowerState);

	// 캐릭터 방향
	UFUNCTION(Reliable, Server)
	void ChangePlayerDir(EPlayerMoveDir _Dir);
	void ChangePlayerDir_Implementation(EPlayerMoveDir _Dir);

	// 아이템 변경
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void PickUpItem();
	void PickUpItem_Implementation();

	// 아이템 생성 -> 드랍
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void CharacterPlayerToDropItem();
	void CharacterPlayerToDropItem_Implementation();

	// Fire Ray Cast
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void FireRayCast(float _DeltaTime);
	void FireRayCast_Implementation(float _DeltaTime);

	// 공격 몽타주 서버
	UFUNCTION(Reliable, Server)
	void ChangeMontage();
	void ChangeMontage_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void ClientChangeMontage();
	void ClientChangeMontage_Implementation();

	/// <summary>
	/// Crouch 에 대한 카메라 이동
	/// </summary>
	UFUNCTION()
	void CrouchCameraMove();

	// == Client ==
private :	
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision);
	
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapEnd();

	UFUNCTION()
	void UpdatePlayerHp(float _DeltaTime);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsServer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsClient = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsCanControlled = false;

	UPROPERTY(Category = "PlayerNet", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Token = -1;

public :
	// == 인칭 변경 함수 ==
	UFUNCTION()
	void ChangePOV();

	// 리로드.
	UFUNCTION()
	void CharacterReload();

	UFUNCTION(BlueprintCallable)
	void HandAttackCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision);

	// Notify State에서 호출.
	UFUNCTION()
	void ChangeHandAttackCollisionProfile(FName _Name);

	UFUNCTION()
	void NetCheck();

	UFUNCTION()
	void SendTokenToHpBarWidget();
};

/** BP
* MovementComponent -> WalkableFloorAngle 의 값을 60.0으로 수정.
*/