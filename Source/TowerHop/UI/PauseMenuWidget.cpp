#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TowerHop/TowerHopGameInstance.h"
#include "TowerHop/Controllers/PlayerCharacterController.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UTowerHopGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		if (NewGameButton)
		{
			NewGameButton->OnClicked.AddDynamic(GameInstance, &UTowerHopGameInstance::StartNewGame);
		}
		if (GraphicsButton)
		{
			GraphicsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnGraphicsButtonClick);
		}
		if (MainMenuButton)
		{
			MainMenuButton->OnClicked.AddDynamic(GameInstance, &UTowerHopGameInstance::ReturnToMainMenu);
		}
		if (QuitButton)
		{
			QuitButton->OnClicked.AddDynamic(GameInstance, &UTowerHopGameInstance::QuitGame);
		}
		UpdateGraphicsButtonText();
	}

	PlayerController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		if (ResumeButton)
		{
			ResumeButton->OnClicked.AddDynamic(PlayerController, &APlayerCharacterController::ResumeGame);
		}
	}
}

void UPauseMenuWidget::SetFocus() const
{
	ResumeButton->SetFocus();
}

void UPauseMenuWidget::OnGraphicsButtonClick()
{
	if (!GameInstance) return;

	GameInstance->CycleGraphicsQuality();
	UpdateGraphicsButtonText();
}

void UPauseMenuWidget::UpdateGraphicsButtonText()
{
	if (!GameInstance || !GraphicsButtonText) return;

	FText text = FText::FromString("Quality: " + GameInstance->GraphicsQualityText());
	GraphicsButtonText->SetText(text);
}
