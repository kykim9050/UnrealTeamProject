// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NetDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNetDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	inline FString GetIP()
	{
		return IP;
	}
	inline FString GetPORT()
	{
		return PORT;
	}
	inline bool GetIsServer()
	{
		return IsServer;
	}

	void SetIP(FString _IP)
	{
		IP = _IP;
	}

	void SetPORT(FString _PORT)
	{
		PORT = _PORT;
	}

	void SetIsServer(bool _IsServer)
	{
		IsServer = _IsServer;
	}

protected:

private:
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString IP = "127.0.0.1";

	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString PORT = "30001";

	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	bool IsServer = false;
};
