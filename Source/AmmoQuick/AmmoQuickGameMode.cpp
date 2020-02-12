// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AmmoQuickGameMode.h"
#include "AmmoQuickHUD.h"
#include "AmmoQuickCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAmmoQuickGameMode::AAmmoQuickGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAmmoQuickHUD::StaticClass();
}
