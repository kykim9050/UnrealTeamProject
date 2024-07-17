// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Object/TestSwtich.h"
#include "Components/CapsuleComponent.h"
#include "TestLevel/Character/TestCharacter.h"
#include "PartDevLevel/Object/TestDoor.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/MapObjDataRow.h"


// Sets default values
ATestSwtich::ATestSwtich()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwitchCollision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	Mesh->SetupAttachment(Collision);

}

// Called when the game starts or when spawned
void ATestSwtich::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	if (nullptr == Inst)
	{
		UE_LOG(ObjectLog, Fatal, TEXT("%S(%u)> if (nullptr == Inst)"), __FUNCTION__, __LINE__);
		return;
	}

	const FMapObjDataRow* TableData = Inst->GetMapObjDataTable(FName(TEXT("Armory_Switch")));
	Mesh->SetStaticMesh(TableData->GetMesh());
}

// Called every frame
void ATestSwtich::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestSwtich::CharactorCollision(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	ATestCharacter* CharactorCheck = Cast<ATestCharacter>(_OtherActor);
	if (nullptr == CharactorCheck)
	{
		return;
	}

	CharctorOn = true;
}

void ATestSwtich::DoorSwitch(AActor* _OtherActor)
{
	bool IsDoorOpen = ConnectedDoor->GetIsDoorOpen();
	
	ATestDoor* TestDoor = Cast<ATestDoor>(_OtherActor);
	// 열기
	if (true == CharctorOn && false == IsDoorOpen)
	{
		// 문을 가지고 와서 cast해주고, Doortime을 0.0으로 set해준다.
		ConnectedDoor->SetIsDoorOpen(true);
		int a = 0;
	}
	// 닫기
	else if (true == CharctorOn && true == IsDoorOpen)
	{
		// 문을 가지고 와서 cast해주고, Doortime을 0.0으로 set해준다.
		ConnectedDoor->SetIsDoorOpen(false);
		int a = 0;
	}

}

