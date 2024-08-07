// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Base/BossMonsterBase.h"
#include "MainGameLevel/Monster/Base/BossMonsterData.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/BossMonsterDataRow.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

ABossMonsterBase::ABossMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Attack Component
	AttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Component"));
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackComponent->SetupAttachment(RootComponent);

}

void ABossMonsterBase::Damaged(float Damage)
{
	Super::Damaged(Damage);

	// Server Only
	if (false == HasAuthority() || 0.0f >= SettingData->Hp)
	{
		return;
	}

	SettingData->Hp -= Damage;

	// Dead
	if (0.0f >= SettingData->Hp)
	{
		SettingData->Hp = 0.0f;

		//SetDead();
		ChangeAnimation(EBossMonsterAnim::Dead);
		//AIController->GetBrainComponent()->StopLogic(TEXT("Dead"));
	}
}

void ABossMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 세팅
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == MainGameInst)
	{
		LOG(MonsterLog, Fatal, TEXT("MainGameInstance Is Null"));
		return;
	}

	const FBossMonsterDataRow* BaseData = MainGameInst->GetBossMonsterData(BaseDataName);
	if (nullptr == BaseData)
	{
		LOG(MonsterLog, Fatal, TEXT("BaseData Is Null"));
		return;
	}

	InitData(BaseData);
	if (nullptr == SettingData)
	{
		LOG(MonsterLog, Fatal, TEXT("SettingData Is Null"));
		return;
	}

	// 애니메이션 세팅
	AnimInst = Cast<UMainAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInst)
	{
		LOG(MonsterLog, Fatal, TEXT("AnimInst Is Null"));
		return;
	}

	for (TPair<EBossMonsterAnim, UAnimMontage*> AnimMontageGroup : BaseData->AnimMontages)
	{
		AnimInst->PushAnimation(AnimMontageGroup.Key, AnimMontageGroup.Value);
	}

	// 서버 체크
	if (false == HasAuthority())
	{
		return;
	}

	// AI 컨트롤러 세팅
	AIController = GetController<ABossMonsterAIController>();
	if (nullptr == AIController)
	{
		LOG(MonsterLog, Fatal, TEXT("AIController Is Null"));
		return;
	}

}

void ABossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimInst->ChangeAnimation(AnimType);
}

void ABossMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABossMonsterBase, AnimType);
}

void ABossMonsterBase::ChangeAnimation(uint8 Type)
{
	AnimType = Type;
}

