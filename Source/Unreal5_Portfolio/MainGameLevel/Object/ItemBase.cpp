// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/ItemBase.h"
#include "Components/CapsuleComponent.h"
#include <Global/MainGameInstance.h>
#include "Global/ContentsLog.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetIsReplicated(true);
	StaticMeshComponent->bHiddenInSceneCapture = true;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();
	ItemData = Inst->GetItemData(*ItemDataName);
	if (nullptr == ItemData)
	{
		LOG(ObjectLog, Fatal, "ItemData is null.");
	}
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AItemBase::DestroyItem_Implementation()
//{
//	this->Destroy();
//}