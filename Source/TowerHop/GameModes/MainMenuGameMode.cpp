#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/Controllers/MainMenuController.h"
#include "TowerHop/World/MainMenuCameraPawn.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass = AMainMenuCameraPawn::StaticClass();
	PlayerControllerClass = AMainMenuController::StaticClass();
}

void AMainMenuGameMode::StartPlay()
{
	Super::StartPlay();

	APawn* CameraPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller && CameraPawn)
	{
		Controller->SetViewTarget(CameraPawn);
	}
}
