// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/Lobby/LobbyCharacter.h"
#include "MainGameLevel/LobbyGameMode.h"
#include "MainGameLevel/UI/Lobby/MainLobbyHUD.h"
#include "MainGameLevel/UI/Lobby/PlayerLobbyUserWidget.h"

#include "Global/MainGameInstance.h"

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
	Super::BeginPlay();

	IsServerPtr = GetWorld()->GetAuthGameMode();
	if (nullptr != IsServerPtr)
	{
		// Server에 생긴 캐릭터라면 게임모드의 PlayerCount를 + 1
		ALobbyGameMode* lobby = Cast<ALobbyGameMode>(IsServerPtr);
		int pc = lobby->GetPlayerCount();
		lobby->SetPlayerCount(pc + 1);

		MyOrder = pc; // 0, 1, 2, 3
	}
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

	if (false == SetWidgetNickName)
	{
		SetWidgetNickName = true;

		UMainGameInstance* Inst = GetGameInstance<UMainGameInstance>();

		APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (nullptr != Con)
		{
			AMainLobbyHUD* MyHUD = Cast<AMainLobbyHUD>(Con->GetHUD());		
			Cast<UPlayerLobbyUserWidget>(MyHUD->GetWidget(EUserWidgetType::LobbyButton))->LobbyPlayerName(MyOrder, FText::FromString(Inst->GetMainNickName()));
		}
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
}


void ALobbyCharacter::ClientReady_Implementation()
{
	ALobbyGameMode* lobby = Cast<ALobbyGameMode>(IsServerPtr);
	lobby->SetReadyCount(lobby->GetReadyCount() + 1);
}
