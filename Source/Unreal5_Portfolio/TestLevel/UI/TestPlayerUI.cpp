// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestPlayerUI.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestCharacter.h"
#include "Global/MainGameInstance.h"
#include "Global/DataTable/PlayerDataRow.h"

void UTestPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
 
	MyCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Inst = GetWorld()->GetGameInstanceChecked<UMainGameInstance>();
	MaxHp = static_cast<float>(Inst->GetPlayerData(FName("TestPlayer"))->GetHp());
}

void UTestPlayerUI::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);
}

float UTestPlayerUI::HPUpdate()
{
	CurHp = static_cast<float>(MyCharacter->GetPlayerHp());
	
	// 현재 체력 / MAX 체력 
	return CurHp / MaxHp;
}
