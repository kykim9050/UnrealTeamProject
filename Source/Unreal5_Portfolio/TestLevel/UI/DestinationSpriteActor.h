// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinationSpriteActor.generated.h"

UCLASS()
class UNREAL5_PORTFOLIO_API ADestinationSpriteActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestinationSpriteActor();
	void SetDestinationValue(float _x,float _y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class UPaperSpriteComponent* sprite = nullptr;
};
