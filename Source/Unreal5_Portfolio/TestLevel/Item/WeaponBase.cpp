// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/WeaponBase.h"
#include "TestLevel/Item/PickUpComponent.h"
#include "TestLevel/Item/WeaponComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("FPS_Weapon"));
	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("FPS_PickUp"));

	WeaponComponent->SetupAttachment(RootComponent);
	PickUpComponent->SetupAttachment(WeaponComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponComponent->SetCollisionProfileName(FName(TEXT("NoCollision")));
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

