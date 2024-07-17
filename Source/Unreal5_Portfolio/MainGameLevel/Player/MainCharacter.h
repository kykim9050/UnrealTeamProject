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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	// 미니맵 아이콘
	//UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UTestMinimapIconComponent* MinimapIconComponent = nullptr;
	// 맵에 있는 아이템 탐색 콜리전
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GetMapItemCollisonComponent = nullptr;
	// 버리는 아이템 생성 위치
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CreateItemComponent = nullptr;

	// 몽타주 변경을 위한 AnimInstance
	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnimInst;


	// == State, Posture ==
	
	// 플레이어 자세 유형
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerPosture PostureValue = EPlayerPosture::Barehand;


	// == 인칭 변경 변수 ==
	UPROPERTY()
	bool IsFPV = true;

	// == Inventory ==




	// 맵에 있는 무기 Data
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* GetMapItemData = nullptr;

	// 현재 아이템 Index
	UPROPERTY(VisibleAnywhere)
	int CurItemIndex = -1;

	// 현재 아이템 정보.
	UPROPERTY(VisibleAnywhere)
	TArray<struct FPlayerItemInformation> ItemSlot;

	// 하체 정보
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerLowerState LowerStateValue = EPlayerLowerState::Idle;

	// 상체 정보


	// == Server ==
public :
	// 상채 변경
	UFUNCTION(Reliable, Server)
	void ChangePosture(EPlayerPosture _Type);
	void ChangePosture_Implementation(EPlayerPosture _Type);

	// 하제 변경
	UFUNCTION(Reliable, Server)
	void ChangeLowerState();
	void ChangeLowerState_Implementation();

	// 아이템 변경
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void PickUpItem();
	void PickUpItem_Implementation();

	// 아이템 생성 -> 드랍
	UFUNCTION(Reliable, Server, BlueprintCallable)
	void CharacterPlayerToDropItem(FName _ItemName, FTransform _Transform);
	void CharacterPlayerToDropItem_Implementation(FName _ItemName, FTransform _Transform);

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

	// == Client ==
private :	
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapStart(AActor* _OtherActor, UPrimitiveComponent* _Collision);
	
	UFUNCTION(BlueprintCallable)
	void MapItemOverlapEnd();
	
public :
	// == 인칭 변경 함수 ==
	UFUNCTION()
	void ChangePOV();
};
