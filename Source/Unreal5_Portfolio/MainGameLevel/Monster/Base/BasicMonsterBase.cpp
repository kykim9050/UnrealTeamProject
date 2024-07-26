// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Base/BasicMonsterBase.h"
#include "MainGameLevel/Monster/Animation/BasicMonsterAnimInstance.h"
#include "MainGameLevel/Monster/AI/BasicMonsterAIController.h"
#include "MainGameLevel/Player/MainPlayerState.h"
#include "MainGameLevel/Player/MainCharacter.h"

#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "BrainComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

ABasicMonsterBase::ABasicMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Attack Component
	AttackComponent = CreateDefaultSubobject<USphereComponent>("Attack Component");
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackComponent->SetupAttachment(RootComponent);

	// Dissolve
	DeadTimelineFinish.BindUFunction(this, "DeadFinish");
	DeadDissolveCallBack.BindUFunction(this, "DeadDissolveInterp");

}

void ABasicMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasicMonsterBase, AnimType);
	DOREPLIFETIME(ABasicMonsterBase, AnimIndex);
}

void ABasicMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 데이터 세팅
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	const FMonsterDataRow* BaseData = MainGameInst->GetMonsterData(BaseDataName);

	if (nullptr == BaseData)
	{
		LOG(MonsterLog, Fatal, "BaseData Is Null");
		return;
	}

	SettingData = NewObject<UMonsterData>(this);
	SettingData->BaseData = BaseData;
	SettingData->AttackDamage = 34.0f;
	SettingData->OriginPos = GetActorLocation();

	// 애니메이션 세팅
	AnimInst = Cast<UBasicMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	TMap<EBasicMonsterAnim, FAnimMontageGroup> AllAnimMontages = BaseData->GetAllAnimMontage();
	for (TPair<EBasicMonsterAnim, FAnimMontageGroup> AnimMontageGroup : AllAnimMontages)
	{
		AnimInst->PushAnimation(AnimMontageGroup.Key, AnimMontageGroup.Value);
	}	

	// 서버 체크
	if (false == HasAuthority())
	{
		return;
	}

	// AI 컨트롤러 세팅
	AIController = GetController<ABasicMonsterAIController>();
	AIController->GetBlackboardComponent()->SetValueAsObject("MonsterData", SettingData);

	AttackComponent->OnComponentEndOverlap.AddDynamic(this, &ABasicMonsterBase::OnAttackOverlapEnd);
}

void ABasicMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimInst->ChangeAnimation(AnimType, AnimIndex);
	DeadTimeLine.TickTimeline(DeltaTime);
}

void ABasicMonsterBase::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UBlackboardComponent* BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	if (nullptr == BlackBoard)
	{
		return;
	}

	EBasicMonsterState MonsterState = static_cast<EBasicMonsterState>(BlackBoard->GetValueAsEnum("State"));
	AMainCharacter* HitCharacter = Cast<AMainCharacter>(OtherActor);
	if (nullptr != HitCharacter && EBasicMonsterState::Attack == MonsterState)
	{
		AMainPlayerState* HitPlayerState = Cast<AMainPlayerState>(HitCharacter->GetPlayerState());
		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, "HitPlayerState Is Not Valid");
		}

		HitPlayerState->AddDamage(SettingData->AttackDamage);
	}
}

void ABasicMonsterBase::ChangeRandomAnimation(uint8 Type)
{
	AnimType = Type;
	AnimInst->SetRandomAnimIndex(Type, AnimIndex);
}

void ABasicMonsterBase::Damaged(float Damage)
{
	// Server Only
	if (false == HasAuthority() || 0.0f >= SettingData->Hp)
	{
		return;
	}

	SettingData->Hp -= Damage;

	// Dead
	if (0.0f >= SettingData->Hp)
	{
		SetDead();
		ChangeRandomAnimation(EBasicMonsterAnim::Dead);
		AIController->GetBrainComponent()->StopLogic("Dead");
	}
}

void ABasicMonsterBase::SetDead_Implementation()
{
	// Effect Setting
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodParticle, GetActorTransform());

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

void ABasicMonsterBase::DeadDissolveInterp(float _Value)
{
	for (UMaterialInstanceDynamic* DynamicMat : DynamicMaterials)
	{
		DynamicMat->SetScalarParameterValue("Dissolve", _Value);
	}
}
