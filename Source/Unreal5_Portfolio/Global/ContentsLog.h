// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(MonsterLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(UILog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ObjectLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(GlobalLog, Log, All);

#define LOG(Category, Verbosity, String)    UE_LOG(Category, Verbosity, \
                                            TEXT("%s"), *FString::Printf(TEXT("%s : {%d} : %s"), \
                                            *FString(__FUNCTION__), __LINE__, String));