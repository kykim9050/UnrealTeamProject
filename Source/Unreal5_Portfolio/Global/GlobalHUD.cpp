// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalHUD.h"

void AGlobalHUD::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void AGlobalHUD::AddDebugString(FString _Text)
{
	int a = 0;
}
#endif