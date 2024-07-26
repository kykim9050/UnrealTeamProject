// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapObjectBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AMapObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapObjectBase();

	virtual void InterAction() { }

	UFUNCTION(BlueprintCallable)
	void SetInfo(FName _InfoName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> InteractObjClass = TSubclassOf<AActor>();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
	{
		return MeshComponent;
	}

	FORCEINLINE class UCapsuleComponent* GetCollisionComponent() const
	{
		return CollisionComponent;
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CollisionComponent = nullptr;
};
