// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Demo.h"
#include "DemoGameMode.h"
#include "DemoCharacter.h"

ADemoGameMode::ADemoGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ADemoCharacter::StaticClass();	
}
