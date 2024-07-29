// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Item/PickUpComponent.h"
#include "TestLevel/Character/TestCharacter.h"

UPickUpComponent::UPickUpComponent()
{
	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPickUpComponent::OnSphereBeginOverlap);
}

void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	if (ATestCharacter* Character = Cast<ATestCharacter>(OtherActor))
	{
		/*bool test = Character->GetPickUp();
		if (true == Character->GetPickUp())
		{
			TriggerPickUpEvent(Character);
		}*/
	}
}

void UPickUpComponent::TriggerPickUpEvent(ATestCharacter* PickUpCharacter)
{
	OnPickUp.Broadcast(PickUpCharacter);
}

void UPickUpComponent::TriggerPutDownEvent(ATestCharacter* PutDownCharacter)
{
	OnPutDown.Broadcast(PutDownCharacter);
}
