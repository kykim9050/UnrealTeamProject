// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"
#include "Net/UnrealNetwork.h"

void UMonsterAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMonsterAnimInstance, RandomIndex);
}

void UMonsterAnimInstance::PushRandomAnimation_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup)
{
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	RandomIndex = MainGameInst->Random.RandRange(0, _MontageGroup.AnimMontages.Num() - 1);
	
	PushMontage(_Key, _MontageGroup);
}

void UMonsterAnimInstance::PushMontage_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup)
{
	PushAnimation(_Key, _MontageGroup.AnimMontages[RandomIndex]);
}