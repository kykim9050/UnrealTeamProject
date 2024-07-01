// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Player, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Monster, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(UI, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Object, Log, All);

#define LOG(Category, Verbosity, String)    UE_LOG(Category, Verbosity, \
                                            TEXT("%s"), *FString::Printf(TEXT("%s : {%d} : %s"), \
                                            *FString(__FUNCTION__), __LINE__, String));