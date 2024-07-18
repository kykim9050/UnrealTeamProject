// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Object/SwitchObject.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"
#include "Components/CapsuleComponent.h"
//#include "MainGameLevel/Object/DoorObject.h"
#include "MainGameLevel/Object/MapObjectBase.h"
#include "Kismet/GameplayStatics.h"


ASwitchObject::ASwitchObject()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASwitchObject::OnOverlapBegin);
}

void ASwitchObject::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == Inst)"), __FUNCTION__, __LINE__);
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(FName(TEXT("Armory_Switch")));
	GetMeshComponent()->SetStaticMesh(TableData->GetMesh());

	SwitchValue = TableData->GetWorkValue();
	InteractObjClass = TableData->GetInteractObjClass();

	//FVector CurPos = GetCollisionComponent()->GetComponentLocation();
	//FVector CurActorPos = GetActorLocation();
	//FVector CurMeshPos = GetMeshComponent()->GetComponentLocation();

	GetCollisionComponent()->AddRelativeLocation(CollisionOffset);
	//FVector NextPos = GetCollisionComponent()->GetComponentLocation();
	//FVector NextActorPos = GetActorLocation();
	//FVector NextMeshPos = GetMeshComponent()->GetComponentLocation();
}

void ASwitchObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwitchObject::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		// 클래스 형 받아오고
		AActor* OtherActor = UGameplayStatics::GetActorOfClass(GetWorld(), InteractObjClass);
		
		if (nullptr == OtherActor)
		{
			UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == OtherObj)"), __FUNCTION__, __LINE__);
			return;
		}

		// 해당 클래스 형으로 다운캐스팅하기
		AMapObjectBase* InteractObj = Cast<AMapObjectBase>(OtherActor);

		if (nullptr == InteractObj)
		{
			UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == InteractObj)"), __FUNCTION__, __LINE__);
			return;
		}

		InteractObj->InterAction();
	}
}