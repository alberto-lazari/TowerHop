#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "TowerHop/Characters/PlayerCharacterController.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
	}
	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnNewGameClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitClicked);
	}
}

void UPauseMenuWidget::OnResumeClicked()
{
	if (PlayerController) PlayerController->ResumeGame();
}

void UPauseMenuWidget::OnNewGameClicked()
{
	if (PlayerController) PlayerController->StartNewGame();
}

void UPauseMenuWidget::OnQuitClicked()
{
	if (PlayerController) PlayerController->QuitGame();
}
