#include "DefaultHpBarUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UDefaultHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// MainPlayer, P2, P3, P4마다 HpCaseImage가 다름. 

}

void UDefaultHpBarUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

}

void UDefaultHpBarUserWidget::SetHp(float _percent)
{
	HpProgress->SetPercent(_percent);
}

void UDefaultHpBarUserWidget::SetNickName(FText _nickname)
{
	NickNameBlock->SetText(_nickname);
}
