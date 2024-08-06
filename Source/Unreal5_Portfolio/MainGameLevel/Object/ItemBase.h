// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/DataTable/ItemDataRow.h"
#include "ItemBase.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent()
	{
		return StaticMeshComponent;
	}

	FORCEINLINE const FItemDataRow* GetItemData()
	{
		return ItemData;
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(Reliable, Server)
	//void DestroyItem();
	//void DestroyItem_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ItemDataName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent = nullptr;

	const FItemDataRow* ItemData = nullptr;
};
