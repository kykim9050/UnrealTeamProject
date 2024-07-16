// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Animation/MonsterAnimInstance.h"
#include "Global/DataTable/MonsterDataRow.h"


void UMonsterAnimInstance::PushRandomAnimation_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup)
{
	int GroupSize = _MontageGroup.AnimMontages.Num() - 1;
	int Index = FMath::RandRange(0, GroupSize);
	PushMontage(_Key, _MontageGroup.AnimMontages[Index]);
}

void UMonsterAnimInstance::PushMontage_Implementation(uint8 _Key, UAnimMontage* _Montage)
{
	PushAnimation(_Key, _Montage);
}
