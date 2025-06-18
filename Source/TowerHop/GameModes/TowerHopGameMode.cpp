#include "TowerHopGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/Characters/PlayerCharacter.h"
#include "TowerHop/Controllers/PlayerCharacterController.h"
#include "TowerHop/UI/TowerHopHUD.h"

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
	GetWorldTimerManager().SetTimer(RestartTimer, this, &ATowerHopGameMode::GameOver, Delay, false);
}

void ATowerHopGameMode::GameOver()
{
	// On game over return to main menu
	UGameplayStatics::OpenLevel(this, FName("MainMenuMap"), false);
}
