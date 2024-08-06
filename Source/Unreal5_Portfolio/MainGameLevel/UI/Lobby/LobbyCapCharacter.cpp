// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCapCharacter.h"
#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"
#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/PlayerDataRow.h"

#include "Kismet/GameplayStatics.h"

//#include

// Sets default values
ALobbyCapCharacter::ALobbyCapCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	HeadNameComponent = CreateDefaultSubobject<UHeadNameWidgetComponent>(TEXT("HeadNameWidgetComponent"));
	HeadNameComponent->SetupAttachment(RootComponent);
	HeadNameComponent->SetOwnerNoSee(true);
	//HeadNameComponent->SetOwnerPlayer(this);
	HeadNameComponent->bHiddenInSceneCapture = true;
}

// Called when the game starts or when spawned
void ALobbyCapCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == MainGameInst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
		return;
	}

	// 스켈레탈 메쉬 선택
	USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);

	// ABP 선택
	UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerAnimInstance());
	GetMesh()->SetAnimInstanceClass(AnimInst);
	GetMesh()->SetIsReplicated(true);

	HeadNameComponent->SetHeadNameRelativeLocation(FVector(0, 0, 100));
	HeadNameComponent->SetHeadNameRelativeRotation(FVector(0, 0, 180));
}

// Called every frame
void ALobbyCapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// HeadNameComponent가 항상 '나'를 향하도록 회전
	//if (nullptr != HeadNameComponent)
	//{
	//	HeadNameComponent->BilboardRotate(GetActorLocation());
	//}

}

// Called to bind functionality to input
void ALobbyCapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALobbyCapCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyCapCharacter, MyNumber);
}

void ALobbyCapCharacter::SetMyNumber(int _Num)
{
	MyNumber = _Num;

	switch (MyNumber)
	{
	case 0:
		SetActorLocation(FVector(100, -30, 50));
		break;
	case 1:
		SetActorLocation(FVector(120, 30, 40));
		break;
	case 2:
		SetActorLocation(FVector(120, -100, 40));
		break;
	case 3:
		SetActorLocation(FVector(130, 100, 40));
		break;
	default:
		break;
	}
}

void ALobbyCapCharacter::SetMyMesh()
{
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
		return;
	}
	FName MyCharacterType = Inst->GetUIToSelectCharacter();

	if (nullptr == Inst->GetPlayerData(MyCharacterType))
	{
		return;
	}
	// 스켈레탈 메쉬 선택
	USkeletalMesh* PlayerSkeletalMesh = Inst->GetPlayerData(MyCharacterType)->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);

	// ABP 선택
	UClass* AnimInst = Cast<UClass>(Inst->GetPlayerData(MyCharacterType)->GetPlayerAnimInstance());
	GetMesh()->SetAnimInstanceClass(AnimInst);
	GetMesh()->SetIsReplicated(true);
}

void ALobbyCapCharacter::SetEachMesh(FName _TypeName)
{
	if (MyLocalType == _TypeName)
	{
		return;
	}
	else if (MyLocalType != _TypeName)
	{
		MyLocalType = _TypeName;
	}

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
		return;
	}

	if (nullptr == Inst->GetPlayerData(_TypeName))
	{
		return;
	}
	// 스켈레탈 메쉬 선택
	USkeletalMesh* PlayerSkeletalMesh = Inst->GetPlayerData(_TypeName)->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);

	// ABP 선택
	UClass* AnimInst = Cast<UClass>(Inst->GetPlayerData(_TypeName)->GetPlayerAnimInstance());
	GetMesh()->SetAnimInstanceClass(AnimInst);
	GetMesh()->SetIsReplicated(true);
}

void ALobbyCapCharacter::SetHeadNameText(FText _Name)
{
	if(nullptr != HeadNameComponent)
	{
		HeadNameComponent->SetHeadNameWidgetText(_Name);
	}
}


