// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:

protected:

private:
	/// <summary>
	/// Player �̸�
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FString Name = "None";

	/// <summary>
	/// ü��
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	int Hp = 100;

	/// <summary>
	/// �̵� �ӵ�
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float MoveSpeed = 100.0f;

	/// <summary>
	/// ȸ�� �ӵ�
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RotSpeed = 100.0f;

	/// <summary>
	/// �ٱ� �ӵ�
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	float RunSpeed = 2.0f;

	/// <summary>
	/// ���� ��
	/// </summary>
	UPROPERTY(Category = "Parameter", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	bool Jumping = false;
};