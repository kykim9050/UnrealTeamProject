// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"
#include "MainGameLevel/UI/Lobby/MainLobbyHUD.h"
#include "MainGameLevel/UI/Lobby/PlayerLobbyUserWidget.h"
#include "MainGameLevel/UI/Lobby/LobbyCapCharacter.h"
#include "MainGameLevel/LobbyGameMode.h"

#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"

#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	IsServerPtr = GetWorld()->GetAuthGameMode();
	Super::BeginPlay();

	// 서버가 플레이어 수를 세고 내 번호를 지정.
	if (nullptr != IsServerPtr)
	{
		// Server에 생긴 캐릭터라면 게임모드의 PlayerCount를 + 1
		ALobbyGameMode* lobby = Cast<ALobbyGameMode>(IsServerPtr);
		int pc = lobby->GetPlayerCount();
		lobby->SetPlayerCount(pc + 1);

		MyOrder = pc; // 0, 1, 2, 3
	}
	// 나의 마네킹에 내 번호를 알려줌. (각 플레이어에 해당하는 마네킹은 BP에서 Spawn됨 => Super::BeginPlay 내에서 실행됨)
	if(nullptr != MyMannequin)
	{
		MyMannequin->SetMyNumber(MyOrder);
	}

	// Instance에 저장돼있는 닉네임 모두가 알 수 있도록 하는 작업. 
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
	}
	FText InstName = FText::FromString(Inst->GetMainNickName());
	SendNicknames(InstName);
}

// Called every frame
void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 준비 완료 시 서버에게 알려줌. 
	if (true == ReadyClicked)
	{
		ClientReady();
		ReadyClicked = false;
	}

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
	}

	// 마네킹을 플레이어에서 직접 업데이트 (메시, 닉네임)
	if (nullptr != MyMannequin)
	{
		MyMannequin->SetEachMesh(MyChracterType);
		MyMannequin->SetHeadNameText(MyNickName);
	}
}

// Called to bind functionality to input
void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ALobbyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyCharacter, MyOrder);
	DOREPLIFETIME(ALobbyCharacter, MyChracterType);
	DOREPLIFETIME(ALobbyCharacter, MyMannequin);
	DOREPLIFETIME(ALobbyCharacter, MyNickName);
}


void ALobbyCharacter::ClientReady_Implementation()
{
	ALobbyGameMode* lobby = Cast<ALobbyGameMode>(IsServerPtr);
	if (nullptr == lobby)
	{
		return;
	}

	lobby->SetReadyCount(lobby->GetReadyCount() + 1);
}

void ALobbyCharacter::ClientChangedMesh_Implementation(FName _NewType)
{
	MyChracterType = _NewType;
}

void ALobbyCharacter::SendNicknames_Implementation(const FText& _Nickname)
{
	MyNickName = _Nickname;
}
