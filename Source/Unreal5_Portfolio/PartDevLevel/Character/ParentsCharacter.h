// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentsCharacter.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AParentsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParentsCharacter();

	// Call Notify
	virtual void AnimationEnd();
	virtual void AnimationEnd(FString _CurMontage);

protected:
	// Component
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemSocketMesh = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	
	UPROPERTY(Category = "Contents", VisibleDefaultsOnly)
	USkeletalMeshComponent* FPVMesh = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FPVItemSocketMesh = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GetMapItemCollisionComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HandAttackComponent = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTestMinimapIconComponent* MinimapIconComponent = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UHeadNameWidgetComponent* HeadNameComponent = nullptr;







	// POV
	const FVector CameraRelLoc = FVector(0.0f, 60.0f, 110.0f);
	const FVector FPVCameraRelLoc = FVector(10.0f, 0.0f, 72.0f);
	const FVector FPVCameraRelLoc_Crouch = FVector(10.0f, 0.0f, 10.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void ChangeHandAttackCollisionProfile(FName _Name);
};
