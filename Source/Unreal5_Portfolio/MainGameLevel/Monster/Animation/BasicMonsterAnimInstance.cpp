// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/Monster/Animation/BasicMonsterAnimInstance.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/MainGameInstance.h"
#include "Net/UnrealNetwork.h"

void UBasicMonsterAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBasicMonsterAnimInstance, RandomIndex);
}

void UBasicMonsterAnimInstance::PushRandomAnimation_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup)
{
	UMainGameInstance* MainGameInst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	RandomIndex = MainGameInst->Random.RandRange(0, _MontageGroup.AnimMontages.Num() - 1);

	PushMontage(_Key, _MontageGroup);
}

void UBasicMonsterAnimInstance::PushMontage_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup)
{
	PushAnimation(_Key, _MontageGroup.AnimMontages[RandomIndex]);
}
