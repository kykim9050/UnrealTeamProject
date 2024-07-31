// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestArea.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"
#include "Components/CapsuleComponent.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameLevel/Object/Bomb.h"
#include "Components/BoxComponent.h"

ATestArea::ATestArea()
{
	bReplicates = true;

	SetBombBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SetBombBox"));
	SetBombBox->SetupAttachment(GetRootComponent());

}

void ATestArea::BeginPlay()
{
	Super::BeginPlay();
}

void ATestArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != HaveBomb && BombState::Install == HaveBomb->CurBombState)
	{
		TimeFlow(DeltaTime);
	}

}

void ATestArea::InterAction()
{
	Super::InterAction();

	if (0.f >= InstallBombTime)
	{
		SetBomb();
	}



}

void ATestArea::ResetBombTime()
{
	InstallBombTime = 3.f;
}

void ATestArea::InstallBomb(float _DeltaTime)
{
	InstallBombTime -= _DeltaTime;
}


void ATestArea::SetBomb()
{
	if (nullptr != InteractObjClass)
	{
		AActor* OtherActor = UGameplayStatics::GetActorOfClass(GetWorld(), InteractObjClass);

		if (nullptr == OtherActor)
		{
			UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == OtherObj)"), __FUNCTION__, __LINE__);
			return;
		}

		// 해당 클래스 형으로 다운캐스팅하기
		ABomb* InteractObj = Cast<ABomb>(OtherActor);

		if (nullptr == InteractObj)
		{
			UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == InteractObj)"), __FUNCTION__, __LINE__);
			return;
		}

		InteractObj->SetActorLocation(SetBombBox->GetComponentLocation());
		InteractObj->CurBombState = BombState::Install;
		HaveBomb = InteractObj;

	}

}

void ATestArea::TimeFlow(float _DeltaTime)
{
	BombTime -= _DeltaTime;
}
