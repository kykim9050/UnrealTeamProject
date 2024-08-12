// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameLevel/UI/InGame/HeadNameWidgetComponent.h"
#include "MainGameLevel/UI/InGame/HeadNameUserWidget.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Global/ContentsLog.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "TimerManager.h"


UHeadNameWidgetComponent::UHeadNameWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HeadNameWidget(TEXT("/Game/BluePrint/MainGameLevel/UI/InGame/WBP_HeadName"));
	if (true == HeadNameWidget.Succeeded())
	{
		SetWidgetClass(HeadNameWidget.Class);
	}
	else
	{
		LOG(UILog, Fatal, "WBP_HeadName Not Found");
		int a = 0;
	}

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UHeadNameWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetRelativeLocation(FVector(0, 0, 70));
	SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(0.f, 0.f, 0.f));
	SetRelativeRotation(Q);

	UMainGameInstance* Inst = UMainGameBlueprintFunctionLibrary::GetMainGameInstance(GetWorld());
	if (nullptr == Inst)
	{
		LOG(UILog, Fatal, "MainGameInstance is Null");
	}
	FText InstName = FText::FromString(Inst->GetMainNickName());
	SendNicknames(InstName);

	GetWorld()->GetTimerManager().SetTimer(HeadNameHandle, [this]()
		{
			SetHeadNameWidgetText(HeadNameText);
		}, 5.0f, false);
}

void UHeadNameWidgetComponent::InitWidget()
{
	Super::InitWidget();

	//	SetHeadNameWidgetText(HeadNameText);
}

void UHeadNameWidgetComponent::BilboardRotate(FVector _WorldLocation)
{
	FVector CameraLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(_WorldLocation, CameraLoc);
	FVector X = FVector::ZeroVector;
	FVector Y = FVector::ZeroVector;
	FVector Z = FVector::ZeroVector;
	UKismetMathLibrary::GetAxes(Rot, X, Y, Z);
	FRotator Res = UKismetMathLibrary::Conv_VectorToRotator(X);
	Res = FRotator(0.0f, Res.Yaw, 0.0f);
	SetWorldRotation(Res);
}

void UHeadNameWidgetComponent::SetHeadNameRelativeLocation(FVector _Loc)
{
	SetRelativeLocation(_Loc);
}

void UHeadNameWidgetComponent::SetHeadNameRelativeRotation(FVector _Rot)
{
	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, _Rot);
	SetRelativeRotation(Q);
}

void UHeadNameWidgetComponent::SetHeadNameWidgetText(FText _Name)
{
	UHeadNameUserWidget* widget = Cast<UHeadNameUserWidget>(GetUserWidgetObject());
	if (nullptr != widget)
	{
		widget->SetNameText(_Name);
	}
}

void UHeadNameWidgetComponent::SendNicknames_Implementation(const FText& _Nickname)
{
	HeadNameText = _Nickname;
}

void UHeadNameWidgetComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHeadNameWidgetComponent, HeadNameText);

}