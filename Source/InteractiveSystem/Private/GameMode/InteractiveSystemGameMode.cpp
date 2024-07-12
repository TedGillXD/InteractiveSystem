// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/InteractiveSystemGameMode.h"
#include "Character/InteractiveSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInteractiveSystemGameMode::AInteractiveSystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
