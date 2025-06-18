#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "TowerHop/Controllers/MainMenuController.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<AMainMenuController>(UGameplayStatics::GetPlayerController(this, 0));

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::OnNewGameClicked()
{
	if (Controller) Controller->StartNewGame();
}

void UMainMenuWidget::OnQuitClicked()
{
	if (Controller) Controller->QuitGame();
}
