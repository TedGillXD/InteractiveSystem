// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InteractiveSystemGameMode.generated.h"

UCLASS(minimalapi)
class AInteractiveSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInteractiveSystemGameMode();

	// Functions for Room 1
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Room1 Funcs")
	bool CheckStatueStatus();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Room1 Funcs")
	void GenerateRoom1Key();
};



