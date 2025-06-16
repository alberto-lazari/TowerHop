#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "TowerHop/UI/PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (PauseMenuClass)
	{
		PauseMenu = CreateWidget<UPauseMenuWidget>(this, PauseMenuClass);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();

			// Start game on pause/main menu
			PauseGame();
		}
	}
}

void APlayerCharacterController::TogglePauseMenu()
{
	// Toggle pause state
	bIsPaused = !bIsPaused;

	if (bIsPaused) PauseGame();
	else ResumeGame();
}

void APlayerCharacterController::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (PauseMenu)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacterController::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (PauseMenu)
	{
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::StartNewGame()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));

	// Game starts on main menu, skip that
	ResumeGame();
}

void APlayerCharacterController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
}
