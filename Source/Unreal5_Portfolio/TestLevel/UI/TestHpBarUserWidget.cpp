// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestHpBarUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestCharacter.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"
#include "Components/ProgressBar.h"
#include "TestLevel/Character/TestPlayerState.h"


void UTestHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	MaxHp = static_cast<float>(Inst->GetPlayerData(FName("TestPlayer"))->GetHp());
}

void UTestHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

	PB_HpBar->SetPercent(HPUpdate());
}

float UTestHpBarUserWidget::HPUpdate()
{
	//CurHp = static_cast<float>(MyCharacter->GetPlayerHp());
	ATestPlayerState* MyPlayerState = Cast<ATestPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	CurHp = MyPlayerState->GetPlayerHp();

	// 현재 체력 / MAX 체력 
	return CurHp / MaxHp;
}
