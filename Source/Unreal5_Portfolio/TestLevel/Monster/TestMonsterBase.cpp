// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterBase.h"
#include "TestMonsterBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsEnum.h"

// Sets default values
ATestMonsterBase::ATestMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	// 클라이언트는 딱히 할게 없다.
	if (nullptr == GetController())
	{
		return;
	}

	BaseData = MainGameInst->GetMonsterData(BaseDataName);
	if (nullptr == BaseData)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		return;
	}

	//  몬스터 데이터 세팅
	SettingData = NewObject<UMonsterData>(this);
	SettingData->Data = BaseData;
	SettingData->OriginPos = GetActorLocation();
	SettingData->Min_PatrolRange = 300.0f;
	SettingData->Max_PatrolRange = 600.0f;

	ATestMonsterBaseAIController* AIController = GetController<ATestMonsterBaseAIController>();
	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("MonsterData"), SettingData);
}

// Called every frame
void ATestMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

