// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlurParGameMode.h"
#include "BlurParCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlurParGameMode::ABlurParGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
