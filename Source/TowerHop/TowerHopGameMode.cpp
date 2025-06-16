// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerHopGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/PlayerCharacterController.h"
#include "UI/TowerHopHUD.h"

ATowerHopGameMode::ATowerHopGameMode()
{
	// Set default pawn class to player's blueprint
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set custom player controller
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	// Set HUD
	HUDClass = ATowerHopHUD::StaticClass();
}

void ATowerHopGameMode::HandlePlayerDeath()
{
	// Delay game restart
	float Delay = 1.5f;
	GetWorldTimerManager().SetTimer(RestartTimer, this, &ATowerHopGameMode::ResetLevel, Delay, false);
}

void ATowerHopGameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}
