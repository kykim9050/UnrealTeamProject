// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/LobbyGameMode.h"

#include "Global/MainGameInstance.h"


void ALobbyGameMode::ListenServerOn()	// BP에서 실행 
{
	UMainGameInstance* Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		FString Port = Inst->CurNetInfo.GetPORT();
		int PortNumber = FCString::Atoi(*Port);
		if (PortNumber == 0)
		{
			PortNumber = 30001;
			return;
			//UE_LOG(GIMATLog, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		}

		Inst->EnableListenServer(true, PortNumber);
	}
}