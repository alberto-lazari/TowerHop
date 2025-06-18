#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "TowerHop/UI/PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerCharacterController, Log, All);

APlayerCharacterController::APlayerCharacterController()
{
	static ConstructorHelpers::FClassFinder<UPauseMenuWidget> PauseMenuWidgetObj(TEXT("/Game/UI/WBP_PauseMenu"));
	if (PauseMenuWidgetObj.Succeeded())
	{
		PauseMenuWidgetClass = PauseMenuWidgetObj.Class;
	}
	else
	{
		UE_LOG(LogPlayerCharacterController, Error, TEXT("Failed to find WBP_PauseMenu"));
	}
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(this, PauseMenuWidgetClass);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
			SetGamePaused(false);
		}
	}
}

void APlayerCharacterController::SetGamePaused(bool bPaused)
{
	bGamePaused = bPaused;
	UGameplayStatics::SetGamePaused(GetWorld(), bPaused);
	if (bPaused)
	{
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
	}

	if (PauseMenuWidget)
	{
		bShowMouseCursor = bPaused;
		PauseMenuWidget->SetVisibility(bPaused ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::TogglePauseMenu()
{
	SetGamePaused(!bGamePaused);
}

void APlayerCharacterController::ResumeGame()
{
	SetGamePaused(false);
}

void APlayerCharacterController::StartNewGame()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));
}

void APlayerCharacterController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
}
