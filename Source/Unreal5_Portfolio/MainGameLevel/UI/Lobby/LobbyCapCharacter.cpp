// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCapCharacter.h"
#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"

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

	// Ω∫ƒÃ∑π≈ª ∏ﬁΩ¨ º±≈√
	USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);


	// ABP º±≈√
	UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("TestPlayer"))->GetPlayerAnimInstance());
	GetMesh()->SetAnimInstanceClass(AnimInst);
	GetMesh()->SetIsReplicated(true);
}

// Called every frame
void ALobbyCapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		SetActorLocation(FVector(100, -30, 40));
		break;
	case 1:
		SetActorLocation(FVector(120, 30, 0));
		break;
	case 2:
		SetActorLocation(FVector(120, -100, 0));
		break;
	case 3:
		SetActorLocation(FVector(130, 100, 0));
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
	// Ω∫ƒÃ∑π≈ª ∏ﬁΩ¨ º±≈√
	USkeletalMesh* PlayerSkeletalMesh = Inst->GetPlayerData(MyCharacterType)->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);

	// ABP º±≈√
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
	// Ω∫ƒÃ∑π≈ª ∏ﬁΩ¨ º±≈√
	USkeletalMesh* PlayerSkeletalMesh = Inst->GetPlayerData(_TypeName)->GetPlayerSkeletalMesh();
	GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);
	GetMesh()->SetIsReplicated(true);

	// ABP º±≈√
	UClass* AnimInst = Cast<UClass>(Inst->GetPlayerData(_TypeName)->GetPlayerAnimInstance());
	GetMesh()->SetAnimInstanceClass(AnimInst);
	GetMesh()->SetIsReplicated(true);
}


