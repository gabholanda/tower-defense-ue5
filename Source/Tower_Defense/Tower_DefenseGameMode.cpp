// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tower_DefenseGameMode.h"
#include "Tower_DefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATower_DefenseGameMode::ATower_DefenseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
