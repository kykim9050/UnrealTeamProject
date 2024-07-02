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

	/// <summary>
	/// MonsterDataTable 포인터를 받아오는 함수
	/// FName은 생성한 MonsterDataTable 행이름
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	const struct FMonsterDataRow* GetMonsterData(FName _Name);

	/// <summary>
	/// ItemDataTable 포인터를 받아오는 함수
	/// FName은 생성한 ItemDataTable 행 이름
	/// </summary>
	const struct FItemDataRow* GetItemData(FName _Name);


	FNetDataRow CurNetInfo;
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* PlayerDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* NetDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* MonsterDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	UDataTable* ItemDataTable = nullptr;

private:
	UMainGameInstance();
};
