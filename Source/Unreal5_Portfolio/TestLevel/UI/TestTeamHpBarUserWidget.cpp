// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestTeamHpBarUserWidget.h"
#include "Components/ProgressBar.h"
#include "TestPlayHUD.h"
#include "Kismet/GameplayStatics.h"
#include "TestLevel/Character/TestPlayerState.h"
#include "TestLevel/TestPlayMode.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/PlayerDataRow.h"

void UTestTeamHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// 최대 체력값 받아두기
	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	MaxHp = static_cast<float>(Inst->GetPlayerData(FName("TestPlayer"))->GetHp());

	// 각 프로그레스바 Array에 넣어두기
	HpArray.Add(PB_P2HpBar);
	HpArray.Add(PB_P3HpBar);
	HpArray.Add(PB_P4HpBar);
}

void UTestTeamHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

	HPUpdate();
}

void UTestTeamHpBarUserWidget::HPUpdate()
{
	ATestPlayMode* Mode = Cast<ATestPlayMode>(GetWorld()->GetAuthGameMode());
	int b = 0;

	for (int i = 1; i < 4; ++i)
	{
		ATestPlayerState* OtherPlayerState = Cast<ATestPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), i));
		if (nullptr == OtherPlayerState)
		{
			continue;
		}
		HpArray[i - 1]->SetPercent(OtherPlayerState->GetPlayerHp() / MaxHp);
	}
}