// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Base/TestMonsterBase.h"
#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "PartDevLevel/Monster/NonBoss/TestMonsterBaseAIController.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/Character/TestCharacter.h"

#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "MotionWarpingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "BrainComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/ContentsEnum.h"
#include "Global/ContentsLog.h"


// Sets default values
ATestMonsterBase::ATestMonsterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Comp"));
	AttackComponent->SetupAttachment(RootComponent);

	DeadTimelineFinish.BindUFunction(this, "OnDeadFinish");
	DeadDissolveCallBack.BindUFunction(this, "OnDeadDissolveInterp");

	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarp"));
}

// Called when the game starts or when spawned
void ATestMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());

	AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == AnimInst)
	{
		LOG(MonsterLog, Fatal, TEXT("AnimInst Setting Wrong"));
		return;
	}

	const FMonsterDataRow* BaseData = MainGameInst->GetMonsterData(BaseDataName);

	if (nullptr == BaseData)
	{
		LOG(MonsterLog, Fatal, TEXT("BaseData Is Null"));
		return;
	}

	TMap<ETestMonsterAnim, FAnimMontageGroup> AllAnimMontages = BaseData->GetTestAnimMontage();
	for (TPair<ETestMonsterAnim, FAnimMontageGroup> AnimMontageGroup : AllAnimMontages)
	{
		AnimInst->PushAnimation(AnimMontageGroup.Key, AnimMontageGroup.Value);
	}

	//  몬스터 데이터 세팅
	SettingData = NewObject<UTestMonsterDataBase>(this);
	SettingData->BaseData = BaseData;
	SettingData->AttackDamage = 34.0f;
	SettingData->AttackRange = BaseData->GetAttackRange();
	SettingData->OriginPos = GetActorLocation();
	SettingData->SpawnCount = BaseData->GetSpawnRockCount();

	// 클라이언트일 경우
	AIController = GetController<ATestMonsterBaseAIController>();
	if (nullptr == AIController)
	{
		return;
	}

	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("MonsterData"), SettingData);

	AttackComponent->OnComponentEndOverlap.AddDynamic(this, &ATestMonsterBase::OnAttackOverlapEnd);
	// 바인딩 함수 만들기
	SetAttackCollision(false);
}

// Called every frame
void ATestMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeadTimeLine.TickTimeline(DeltaTime);
	AnimInst->ChangeAnimation(AniType, AniIndex);
}

// Called to bind functionality to input
void ATestMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestMonsterBase, AniType);
	DOREPLIFETIME(ATestMonsterBase, AniIndex);
}

void ATestMonsterBase::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Attack(OtherActor, OtherComp);
}

ATestMonsterBaseAIController* ATestMonsterBase::GetAIController()
{
	return Cast<ATestMonsterBaseAIController>(GetController());
}

UMonsterAnimInstance* ATestMonsterBase::GetAnimInstance()
{
	return AnimInst;
}

void ATestMonsterBase::ChangeRandomAnimation(uint8 _Type)
{
	AniType = _Type;
	AnimInst->SetRandomAniIndex(_Type, AniIndex);
}

void ATestMonsterBase::Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	UBlackboardComponent* BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	if (nullptr == BlackBoard)
	{
		return;
	}

	ETestMonsterState MonsterState = static_cast<ETestMonsterState>(BlackBoard->GetValueAsEnum(TEXT("State")));
	ATestCharacter* HitCharacter = Cast<ATestCharacter>(_OtherActor);
	if (nullptr != HitCharacter && (ETestMonsterState::Attack == MonsterState || ETestMonsterState::JumpAttack == MonsterState))
	{
		ATestPlayerState* HitPlayerState = Cast<ATestPlayerState>(HitCharacter->GetPlayerState());

		if (nullptr == HitPlayerState)
		{
			LOG(MonsterLog, Fatal, TEXT("HitPlayerState Is Not Valid"));
		}

		HitPlayerState->AddDamage(SettingData->AttackDamage);
	}
}

void ATestMonsterBase::Damaged(float Damage)
{
	if (false == HasAuthority() || 0.0f >= SettingData->Hp)
	{
		return;
	}

	SettingData->Hp -= Damage;

	if (0.0f >= SettingData->Hp)
	{
		OnDead();
	}
}

void ATestMonsterBase::SetAttackCollision(bool Active)
{
	if (true == Active)
	{
		AttackComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATestMonsterBase::SetChasePlayer()
{
	if (false == HasAuthority())
	{
		return;
	}

	AMainGameState* MainGameState = UMainGameBlueprintFunctionLibrary::GetMainGameState(GetWorld());
	if (nullptr == MainGameState)
	{
		LOG(MonsterLog, Fatal, TEXT("MainGameState Is Nullptr"));
		return;
	}

	UActorGroup* PlayerGroup = MainGameState->GetActorGroup(EObjectType::Player);
	if (nullptr == PlayerGroup)
	{
		LOG(MonsterLog, Fatal, TEXT("PlayerGroup Is Nullptr"));
		return;
	}

	// Find Player
	int MinIndex = -1;
	float MinDistance = FLT_MAX;

	FVector MonsterLocation = GetActorLocation();
	for (int32 i = 0; i < PlayerGroup->Actors.Num(); i++)
	{
		FVector PlayerLocation = PlayerGroup->Actors[i]->GetActorLocation();
		float Diff = (MonsterLocation - PlayerLocation).Size();

		if (Diff < MinDistance)
		{
			MinDistance = Diff;
			MinIndex = i;
		}
	}

	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PlayerGroup->Actors[MinIndex]);
	AIController->GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), static_cast<uint8>(EBasicMonsterState::Chase));
}

UMotionWarpingComponent* ATestMonsterBase::GetMotionWarpingComponent()
{
	return MotionWarpComponent;
}

void ATestMonsterBase::SpawnRock()
{
	if (false == HasAuthority())
	{
		return;
	}

	for (int i = 0; i < SettingData->SpawnCount; i++)
	{
		//GetWorld()->SpawnActor<>();
		LOG(MonsterLog, Log, TEXT("Rock Spawn"));
	}
}

void ATestMonsterBase::SetOnDead_Implementation()
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
	GetCharacterMovement()->SetActive(false);
}

void ATestMonsterBase::OnDead()
{
	SetOnDead();
	ChangeRandomAnimation(ETestMonsterAnim::Dead);

	AIController->GetBrainComponent()->StopLogic("Dead");
	AIController = nullptr;
}

void ATestMonsterBase::OnDeadDissolveInterp(float _Value)
{
	for (UMaterialInstanceDynamic* DynamicMat : DynamicMaterials)
	{
		DynamicMat->SetScalarParameterValue("Dissolve", _Value);
	}
}