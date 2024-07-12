// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/TestCrosshairUserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"

void UTestCrosshairUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWidget* ParentWidget = GetWidgetFromName(TEXT("CanvasPanel"));
	PanelWidget = Cast<UPanelWidget>(ParentWidget);

	AllChildren = PanelWidget->GetAllChildren();

	VerticalCrosshair.Add(PanelWidget->GetChildAt(1));
	VerticalCrosshair.Add(PanelWidget->GetChildAt(2));

	HorizontalCrosshair.Add(PanelWidget->GetChildAt(3));
	HorizontalCrosshair.Add(PanelWidget->GetChildAt(4));

	int a = 0;
}

void UTestCrosshairUserWidget::NativeTick(const FGeometry& _MyGeometry, float _InDeltaTime)
{
	Super::NativeTick(_MyGeometry, _InDeltaTime);

	if (false == DefaultFlag) /* 총 발사 마우스 클릭 시 */
	{
		DefaultFlag = ClickedCrosshair(40.f * _InDeltaTime);
	}

	if(true == DefaultFlag)
	{
		DefaultFlag = DefaultCrosshair(40.f * _InDeltaTime);
	}
}

bool UTestCrosshairUserWidget::ClickedCrosshair(float _Size)
{
	bool IsEnd = false;
	
	for (int i = 0; i < 4; ++i)
	{
		UWidget* child = PanelWidget->GetChildAt(i + 1);
		FWidgetTransform changeSize = child->GetRenderTransform();
		if (abs(changeSize.Translation.X) <= 10.f && abs(changeSize.Translation.Y) <= 10.f)
		{
			FVector2D Vec = FVector2D(dx[i], dy[i]);
			changeSize.Translation = changeSize.Translation + Vec * _Size;
			child->SetRenderTransform(changeSize);
		}
		else
		{
			IsEnd = true;
		}
	}

	return IsEnd;
}

bool UTestCrosshairUserWidget::DefaultCrosshair(float _Size)
{
	bool IsNotDefaultPos = true;

	for (int i = 0; i < 4; ++i)
	{
		UWidget* child = PanelWidget->GetChildAt(i + 1);
		FWidgetTransform changeSize = child->GetRenderTransform();
		if (abs(changeSize.Translation.X) > 0.f && abs(changeSize.Translation.Y) > 0.f)
		{
			FVector2D Vec = FVector2D(dx[i], dy[i]);
			changeSize.Translation = changeSize.Translation - Vec * _Size;
			child->SetRenderTransform(changeSize);
		}
		else
		{
			changeSize.Translation = FVector2D::ZeroVector;
			child->SetRenderTransform(changeSize);
			IsNotDefaultPos = false;
		}
	}

	return IsNotDefaultPos;
}

bool UTestCrosshairUserWidget::ClickedCrosshair_scale(float _Size) // 길이 늘어나는 함수
{
	bool IsEnd = false;
	for (auto vertical : VerticalCrosshair)
	{
		FWidgetTransform changeSize = vertical->GetRenderTransform();
		if(changeSize.Scale.Y <= 1.5f)
		{
			changeSize.Scale = changeSize.Scale + FVector2D(0.f, _Size); // Y가 세로
			vertical->SetRenderTransform(changeSize);
		}
		else
		{
			IsEnd = true;
			return IsEnd;
		}
	}

	for (auto horizontal : HorizontalCrosshair)
	{
		FWidgetTransform changeSize = horizontal->GetRenderTransform();
		if (changeSize.Scale.X <= 1.5f)
		{
			changeSize.Scale = changeSize.Scale + FVector2D(_Size, 0.f); // X가 가로
			horizontal->SetRenderTransform(changeSize);
		}
		else
		{
			IsEnd = true;
			return IsEnd;
		}
	}

	return IsEnd;
}

bool UTestCrosshairUserWidget::DefaultCrosshair_scale(float _Size)
{
	bool IsNotDefault = true;
	for (auto vertical : VerticalCrosshair)
	{
		FWidgetTransform changeSize = vertical->GetRenderTransform();
		if (changeSize.Scale.Y > 1.f) // 줄어드는 코드
		{
			changeSize.Scale = changeSize.Scale - FVector2D(0.f, _Size); // Y가 세로
			vertical->SetRenderTransform(changeSize);
		}
		else
		{
			changeSize.Scale = FVector2D(1.f, 1.f);
			vertical->SetRenderTransform(changeSize);

			IsNotDefault = false;
			return IsNotDefault;
		}
	}

	for (auto horizontal : HorizontalCrosshair)
	{
		FWidgetTransform changeSize = horizontal->GetRenderTransform();
		if (changeSize.Scale.X > 1.f) // 줄어드는 코드
		{
			changeSize.Scale = changeSize.Scale - FVector2D(_Size, 0.f); // X가 가로
			horizontal->SetRenderTransform(changeSize);
		}
		else
		{
			changeSize.Scale = FVector2D(1.f, 1.f);
			horizontal->SetRenderTransform(changeSize);

			IsNotDefault = false;
			return IsNotDefault;
		}
	}

	return IsNotDefault;
}