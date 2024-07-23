// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestBomb.h"
#include "TestLevel/Character/TestCharacter.h"
#include "Components/CapsuleComponent.h"



// Sets default values
ATestBomb::ATestBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BombCollision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void ATestBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (true == CharctorOn)
	{
		BombActivation(DeltaTime);
	}


}

void ATestBomb::CharactorCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestCharacter* CharactorCheck = Cast<ATestCharacter>(_OtherActor);
	if (nullptr == CharactorCheck)
	{
		return;
	}

	CharctorOn = true;

}

void ATestBomb::BombActivation(float _DeltaTime)
{
	// ÆøÅºÈ°¼ºÈ­ UI
	// Å¸ÀÌ¸Ó start
	int a = 0;
}



