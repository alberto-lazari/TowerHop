#include "MainMenuController.h"
#include "Blueprint/UserWidget.h"
#include "TowerHop/UI/MainMenuWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuController, Log, All);

AMainMenuController::AMainMenuController()
{
	static ConstructorHelpers::FClassFinder<UMainMenuWidget> MainMenuWidgetObj(TEXT("/Game/UI/WBP_MainMenu"));
	if (MainMenuWidgetObj.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetObj.Class;
	}
	else
	{
		UE_LOG(LogMainMenuController, Error, TEXT("Failed to find WBP_MainMenu"));
	}
}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	// Create and display main menu
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();

			SetInputMode(FInputModeUIOnly());
			MainMenuWidget->SetFocus();
			bShowMouseCursor = true;
		}
	}
}
