// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/MeleeWP.h"
#include "TestLevel/Item/WeaponBase.h"
#include "TestLevel/Item/PickUpComponent.h"
#include "TestLevel/Item/WeaponComponent.h"
#include "TestLevel/Item/RangedWPComponent.h"
#include "TestLevel/Character/TestCharacter.h"

AMeleeWP::AMeleeWP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<URangedWPComponent>(TEXT("FPS_Weapon"));
	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("FPS_PickUp"));

	WeaponComponent->SetupAttachment(RootComponent);
	PickUpComponent->SetupAttachment(WeaponComponent);

	bReplicates = true;
}

void AMeleeWP::BeginPlay()
{
	Super::BeginPlay();

	PickUpComponent->OnPickUp.AddDynamic(this, &AMeleeWP::HandlePickUp);
	WeaponComponent->SetCollisionProfileName(FName(TEXT("NoCollision")));

}

void AMeleeWP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeWP::HandlePickUp(ATestCharacter* PickUpCharacter)
{
	/*if (WeaponComponent)
	{
		WeaponComponent->AttachWeapon(PickUpCharacter);
		PickUpCharacter->PickUpItem();
		Destroy();
	}*/
}

void AMeleeWP::HandlePutDown(ATestCharacter* PutDownCharacter)
{
}
