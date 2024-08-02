// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCapCharacter.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"
#include "Global/DataTable/PlayerDataRow.h"

//#include

// Sets default values
ALobbyCapCharacter::ALobbyCapCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALobbyCapCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld()->WorldType == EWorldType::Game
		|| GetWorld()->WorldType == EWorldType::PIE)
	{
		UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
		if (nullptr == MainGameInst)
		{
			LOG(UILog, Fatal, "MainGameInstance is Null");
			return;
		}

		// Ω∫ƒÃ∑π≈ª ∏ﬁΩ¨ º±≈√
		USkeletalMesh* PlayerSkeletalMesh = MainGameInst->GetPlayerData(FName("Vanguard"))->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);

		// ABP º±≈√
		UClass* AnimInst = Cast<UClass>(MainGameInst->GetPlayerData(FName("Vanguard"))->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}
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

void ALobbyCapCharacter::SetMyNumber(int _Num)
{
	MyNumber = _Num;
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

	if (GetWorld()->WorldType == EWorldType::Game
		|| GetWorld()->WorldType == EWorldType::PIE)
	{
		// Ω∫ƒÃ∑π≈ª ∏ﬁΩ¨ º±≈√
		USkeletalMesh* PlayerSkeletalMesh = Inst->GetPlayerData(MyCharacterType)->GetPlayerSkeletalMesh();
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh);

		// ABP º±≈√
		UClass* AnimInst = Cast<UClass>(Inst->GetPlayerData(MyCharacterType)->GetPlayerAnimInstance());
		GetMesh()->SetAnimInstanceClass(AnimInst);
	}
}

bool ALobbyCapCharacter::IsMyOrderCharacter()
{
	

	return false;
}

