// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLobbyMode.h"
#include "Global/MainGameInstance.h"


void ATestLobbyMode::ListenServerOn()
{
	UMainGameInstance* Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	if (nullptr != Inst && true == Inst->CurNetInfo.GetIsServer())
	{
		FString Port = Inst->CurNetInfo.GetPORT();
		int PortNumber = FCString::Atoi(*Port);
		if (PortNumber == 0)
		{
			return;
			//UE_LOG(GIMATLog, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		}

		Inst->EnableListenServer(true, PortNumber);
	}
}