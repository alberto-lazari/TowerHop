// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerHopGameMode.h"
#include "TowerHopCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ATowerHopGameMode::ATowerHopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATowerHopGameMode::HandlePlayerDeath()
{
    // Delay game restart
    float Delay = 1.5f;
    GetWorldTimerManager().SetTimer(RestartTimer, this, &ATowerHopGameMode::ResetLevel, Delay, false);
}

void ATowerHopGameMode::ResetLevel()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
