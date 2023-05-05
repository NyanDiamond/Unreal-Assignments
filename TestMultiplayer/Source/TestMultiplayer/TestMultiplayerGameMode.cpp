// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestMultiplayerGameMode.h"
#include "TestMultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestMultiplayerGameMode::ATestMultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
