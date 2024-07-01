// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/Monster/TestMonsterBase.h"
#include "TestMonsterBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

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

	UAnimInstance* Inst = GetMesh()->GetAnimInstance();
	AnimInst = Cast<UMainAnimInstance>(GetMesh()->GetAnimInstance());
	BaseData = MainGameInst->GetMonsterData(BaseDataName);

	if (nullptr == BaseData)
	{
		LOG(MonsterLog, Fatal, TEXT("BaseData Is Null"));
		return;
	}

	TMap<EMonsterAnim, UAnimMontage*> AnimMontages = BaseData->GetAnimMontage();
	for (TPair<EMonsterAnim, class UAnimMontage*> Montage : AnimMontages)
	{
		AnimInst->PushAnimation(Montage.Key, Montage.Value);
	}

	// 클라이언트일 경우
	ATestMonsterBaseAIController* AIController = GetController<ATestMonsterBaseAIController>();
	if (nullptr == AIController)
	{
		return;
	}

	//  몬스터 데이터 세팅
	SettingData = NewObject<UMonsterData>(this);
	SettingData->Data = BaseData;
	SettingData->OriginPos = GetActorLocation();
	SettingData->Max_PatrolRange = 800.0f;

	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("MonsterData"), SettingData);
}

// Called every frame
void ATestMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimInst->ChangeAnimation(AniValue);
}

// Called to bind functionality to input
void ATestMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestMonsterBase, AniValue);
}

ATestMonsterBaseAIController* ATestMonsterBase::GetAIController()
{
	return Cast<ATestMonsterBaseAIController>(GetController());
}

UMainAnimInstance* ATestMonsterBase::GetAnimInstance()
{
	return AnimInst;
}

void ATestMonsterBase::ChangeAnimation_Implementation(uint8 _Type)
{
	AniValue = _Type;
}
