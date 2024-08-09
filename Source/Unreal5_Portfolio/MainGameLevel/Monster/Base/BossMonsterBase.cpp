// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Base/BossMonsterBase.h"
#include "MainGameLevel/Monster/Base/BossMonsterData.h"
#include "MainGameLevel/Monster/BossMonster/AI/BossMonsterAIController.h"
#include "MainGameLevel/UI/InGame/BossHpbarUserWidget.h"
#include "MainGameLevel/Object/ReportObject.h"
#include "MainGameLevel/UI/InGame/MainGameHUD.h"

#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "BrainComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/BossMonsterDataRow.h"
#include "Global/Animation/MainAnimInstance.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

#include "PartDevLevel/Character/ParentsCharacter.h"
#include "TestLevel/Character/TestPlayerState.h"

ABossMonsterBase::ABossMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Attack Component
	AttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Component"));
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackComponent->SetupAttachment(RootComponent);

	// Dissolve
	DeadTimelineFinish.BindUFunction(this, "DeadFinish");
	DeadDissolveCallBack.BindUFunction(this, "DeadDissolveInterp");
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

		SetDead();
		DropItem();
		ChangeAnimation(EBossMonsterAnim::Dead);
		AIController->GetBrainComponent()->StopLogic(TEXT("Dead"));
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

	// 몬스터 체력 UHD
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		LOG(MonsterLog, Fatal, "PlayerController is Null");
		return;
	}

	AMainGameHUD* BossUHD = Cast<AMainGameHUD>(PlayerController->GetHUD());
	if (nullptr == BossUHD)
	{
		LOG(MonsterLog, Fatal, "BossHUD is Null");
		return;
	}

	Cast<UBossHpbarUserWidget>(BossUHD->GetWidget(EUserWidgetType::BossHpbar))->SetBossName(FText::FromString(SettingData->BaseData->BossName));
	Cast<UBossHpbarUserWidget>(BossUHD->GetWidget(EUserWidgetType::BossHpbar))->SetHp(SettingData->Hp, SettingData->BaseData->MaxHp);
	BossUHD->UIOn(EUserWidgetType::BossHpbar);

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

	// Binding
	AttackComponent->OnComponentEndOverlap.AddDynamic(this, &ABossMonsterBase::OnAttackOverlapEnd);
}

void ABossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BossHP_HUDUpdate();
	AnimInst->ChangeAnimation(AnimType);
	DeadTimeLine.TickTimeline(DeltaTime);
}

void ABossMonsterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		return;
	}

	AMainGameHUD* BossUHD = Cast<AMainGameHUD>(PlayerController->GetHUD());
	if (nullptr == BossUHD || nullptr == PlayerController)
	{
		return;
	}

	BossUHD->UIOff(EUserWidgetType::BossHpbar);
}

void ABossMonsterBase::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AParentsCharacter* HitCharacter = Cast<AParentsCharacter>(OtherActor);
	if (nullptr != HitCharacter)
	{
		ATestPlayerState* HitPlayerState = Cast<ATestPlayerState>(HitCharacter->GetPlayerState());
		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
			return;
		}

		HitPlayerState->AddDamage(SettingData->AttackDamage);
	}
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

void ABossMonsterBase::BossHP_HUDUpdate()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		LOG(MonsterLog, Fatal, "PlayerController is Null");
	}

	AMainGameHUD* BossUHD = Cast<AMainGameHUD>(PlayerController->GetHUD());
	if (nullptr == BossUHD)
	{
		LOG(MonsterLog, Fatal, "BossHUD is Null");
		return;
	}

	Cast<UBossHpbarUserWidget>(BossUHD->GetWidget(EUserWidgetType::BossHpbar))->SetHp(SettingData->Hp, SettingData->BaseData->MaxHp);
}

void ABossMonsterBase::SetDead_Implementation()
{
	// Dissolve Setting
	TArray<class UMaterialInterface*> MaterialsInterface = GetMesh()->GetMaterials();

	DynamicMaterials.Empty();
	for (int32 i = 0; i < MaterialsInterface.Num(); i++)
	{
		UMaterialInstanceDynamic* MatInstDynamic = GetMesh()->UPrimitiveComponent::CreateDynamicMaterialInstance(i, MaterialsInterface[i], TEXT("None"));
		DynamicMaterials.Add(MatInstDynamic);
	}

	DeadTimeLine.AddInterpFloat(DeadDissolveCurve, DeadDissolveCallBack);
	DeadTimeLine.SetTimelineFinishedFunc(DeadTimelineFinish);
	DeadTimeLine.SetTimelineLength(3.0f);
	DeadTimeLine.SetLooping(false);
	DeadTimeLine.PlayFromStart();

	// Collision Setting
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

	// MoveMoment Setting
	GetCharacterMovement()->SetActive(false);
}

void ABossMonsterBase::DeadDissolveInterp(float _Value)
{
	for (UMaterialInstanceDynamic* DynamicMat : DynamicMaterials)
	{
		DynamicMat->SetScalarParameterValue("Dissolve", _Value);
	}
}