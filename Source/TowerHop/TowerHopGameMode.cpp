// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerHopGameMode.h"
#include "TowerHopCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATowerHopGameMode::ATowerHopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
