// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Boss/TestBossMonsterBase.h"
#include "TestBossMonsterAIControllerBase.h"

#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"

// Sets default values
ATestBossMonsterBase::ATestBossMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestBossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	MainAnimInst = Cast<UMainAnimInstance>(GetMesh()->GetAnimInstance());
	BossData = MainGameInst->GetBossDataTable(BossDataName);

	if (nullptr == BossData)
	{
		LOG(MonsterLog, Fatal, TEXT("BossData Is Null"));
		return;
	}

	// 몽타주 푸쉬
	TMap<EBossMonsterAnim, UAnimMontage*> AnimMontages = BossData->GetAnimMontage();
	for (TPair<EBossMonsterAnim, class UAnimMontage*> Montage : AnimMontages)
	{
		MainAnimInst->PushAnimation(Montage.Key, Montage.Value);
	}

	//  몬스터 데이터 세팅
	SettingBossData = NewObject<UBossData>(this);
	SettingBossData->Data = BossData;

	// 클라이언트일 경우
	ATestBossMonsterAIControllerBase* AIController = GetController<ATestBossMonsterAIControllerBase>();
	if (nullptr == AIController)
	{
		return;
	}

	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("BossMonsterData"), SettingBossData);

}

// Called every frame
void ATestBossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MainAnimInst->ChangeAnimation(AniValue);
}

// Called to bind functionality to input
void ATestBossMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestBossMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATestBossMonsterBase, AniValue);
}

void ATestBossMonsterBase::ChangeAniValue(uint8 _Type)
{
	AniValue = _Type;
}

ATestBossMonsterAIControllerBase* ATestBossMonsterBase::GetBossAIController()
{
	return Cast<ATestBossMonsterAIControllerBase>(GetController());
}
