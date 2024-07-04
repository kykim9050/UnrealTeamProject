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
	FString GetName() const
	{
		return Name;
	}

	FString GetIP() const
	{
		return IP;
	}
	FString GetPORT() const
	{
		return PORT;
	}
	bool GetIsServer() const
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
	/// <summary>
	/// IP 주인 이름 
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString Name = "Anonymous";

	/// <summary>
	/// IP 주소
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString IP = "127.0.0.1";

	/// <summary>
	/// 포트 번호
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString PORT = "30001";

	/// <summary>
	/// 서버면 true, 아니면 false
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	bool IsServer = false;
};
