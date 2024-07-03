// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/RangedWP.h"
#include "TestLevel/Item/WeaponBase.h"
#include "TestLevel/Item/PickUpComponent.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "TestLevel/Item/RangedWPComponent.h"

// Sets default values
ARangedWP::ARangedWP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<URangedWPComponent>(TEXT("FPS_Weapon"));
	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("FPS_PickUp"));

	WeaponComponent->SetupAttachment(RootComponent);
	PickUpComponent->SetupAttachment(WeaponComponent);
}

// Called when the game starts or when spawned
void ARangedWP::BeginPlay()
{
	Super::BeginPlay();

	PickUpComponent->OnPickUp.AddDynamic(this, &ARangedWP::HandlePickUp);
	WeaponComponent->SetCollisionProfileName(FName(TEXT("NoCollision")));
}

// Called every frame
void ARangedWP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangedWP::HandlePickUp(ATestCharacter* PickUpCharacter)
{
	if (WeaponComponent)
	{
		WeaponComponent->AttachWeapon(PickUpCharacter);
	}
}
