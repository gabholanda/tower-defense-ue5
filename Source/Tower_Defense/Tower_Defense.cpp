// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tower_Defense.h"
#include "Modules/ModuleManager.h"
#include "AbilitySystemGlobals.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Tower_Defense, "Tower_Defense");

#define LOCTEXT_NAMESPACE "Tower_Defense"

void FTowerDefenseModule::StartupModule()
{
	UAbilitySystemGlobals::Get().InitGlobalData();
}

void FTowerDefenseModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
