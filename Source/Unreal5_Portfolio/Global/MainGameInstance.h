// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataTable/NetDataRow.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	/// <summary>
	/// PlayerDataTable 포인터를 받아오는 함수
	/// FName은 생성한 PlayerDataTable 행이름
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	const struct FPlayerDataRow* GetPlayerData(FName _Name);

	/// <summary>
	/// NetDataTable 포인터를 받아오는 함수
	/// FName은 생성한 NetDataTable 행이름
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	const struct FNetDataRow* GetNetData(FName _Name);


	// 서버 접속 테스트 관련 기능들 (추후 제거될 예정)
	FNetDataRow GetNetDataValue(FName _Name);
	FNetDataRow CurNetInfo;
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* PlayerDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* NetDataTable = nullptr;
private:
	UMainGameInstance();
};
