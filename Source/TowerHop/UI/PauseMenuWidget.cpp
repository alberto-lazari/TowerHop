#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/Characters/PlayerCharacterController.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
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
