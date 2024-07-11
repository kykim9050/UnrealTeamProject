// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/TestMonsterBase.h"
#include "TestMonsterBaseAIController.h"
#include "TestLevel/Character/TestCharacter.h"

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

#include "Components/SphereComponent.h"


// Sets default values
ATestMonsterBase::ATestMonsterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Comp"));
	AttackComponent->SetupAttachment(RootComponent);

	LeftClimbComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Left Climb"));
	LeftClimbComponent->SetupAttachment(GetMesh(),  "LeftClimbCheck");

	RightClimbComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Right Climb"));
	RightClimbComponent->SetupAttachment(GetMesh(), "RightClimbCheck");

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	DeadTimelineFinish.BindUFunction(this, FName("OnDeadFinish"));
	DeadDissolveCallBack.BindUFunction(this, FName("OnDeadDissolveInterp"));
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

	//  몬스터 데이터 세팅
	SettingData = NewObject<UMonsterData>(this);
	SettingData->Data = BaseData;
	SettingData->AttackDamage = 34.0f;
	SettingData->OriginPos = GetActorLocation();

	// 클라이언트일 경우
	ATestMonsterBaseAIController* AIController = GetController<ATestMonsterBaseAIController>();
	if (nullptr == AIController)
	{
		return;
	}

	AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("MonsterData"), SettingData);

	AttackComponent->OnComponentEndOverlap.AddDynamic(this, &ATestMonsterBase::OnOverlapEnd);
	// 바인딩 함수 만들기
	//LeftClimbComponent->OnComponentEndOverlap.AddDynamic(this, &ATestMonsterBase::OnOverlapEnd);
	//RightClimbComponent->OnComponentEndOverlap.AddDynamic(this, &ATestMonsterBase::OnOverlapEnd);
	SetAttackCollision(false);
	SetClimbCollision(false);
}

// Called every frame
void ATestMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeadTimeLine.TickTimeline(DeltaTime);
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

void ATestMonsterBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Attack(OtherActor, OtherComp);
}

ATestMonsterBaseAIController* ATestMonsterBase::GetAIController()
{
	return Cast<ATestMonsterBaseAIController>(GetController());
}

UMainAnimInstance* ATestMonsterBase::GetAnimInstance()
{
	return AnimInst;
}

void ATestMonsterBase::ChangeAniValue(uint8 _Type)
{
	AniValue = _Type;
}

void ATestMonsterBase::Attack(AActor* _OtherActor, UPrimitiveComponent* _Collision)
{
	UBlackboardComponent* BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	if (nullptr == BlackBoard)
	{
		return;
	}

	EMonsterState MonsterState = static_cast<EMonsterState>(BlackBoard->GetValueAsEnum(TEXT("State")));
	ATestCharacter* HitCharacter = Cast<ATestCharacter>(_OtherActor);
	if (nullptr != HitCharacter && EMonsterState::Attack == MonsterState)
	{
		HitCharacter->GetDamage(SettingData->AttackDamage);
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

void ATestMonsterBase::SetClimbCollision(bool Active)
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

void ATestMonsterBase::SetDeadCollision_Implementation()
{
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel5);
	AttackComponent->SetCollisionObjectType(ECC_GameTraceChannel5);
	GetCharacterMovement()->SetActive(false);
}

void ATestMonsterBase::SetDeadTimeline_Implementation()
{
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
}

void ATestMonsterBase::OnDead()
{
	SetDeadTimeline();
	SetDeadCollision();
	ChangeAniValue(EMonsterAnim::Dead);

	ATestMonsterBaseAIController* AIController = GetController<ATestMonsterBaseAIController>();
	AIController->UnPossess();
}

void ATestMonsterBase::OnDeadDissolveInterp(float _Value)
{
	for (UMaterialInstanceDynamic* DynamicMat : DynamicMaterials)
	{
		DynamicMat->SetScalarParameterValue("Dissolve", _Value);
	}
}