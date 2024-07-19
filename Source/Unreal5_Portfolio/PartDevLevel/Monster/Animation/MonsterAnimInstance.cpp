// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Net/UnrealNetwork.h"


void UMonsterAnimInstance::SetRandomAniIndex(uint8 Key, int& Index)
{
	if (false == GetOwningActor()->HasAuthority())
	{
		return;
	}

	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	int Size = AllAnimMontages[Key].AnimMontages.Num() - 1;
	Index = MainGameInst->Random.RandRange(0, Size);
}