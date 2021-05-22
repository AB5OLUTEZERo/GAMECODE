// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZEROGameMode.h"
#include "ZEROCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZEROGameMode::AZEROGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
