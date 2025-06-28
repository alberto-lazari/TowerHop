#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TowerHop/TowerHopGameInstance.h"

void UMainMenuWidget::NativeConstruct()
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
			GraphicsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGraphicsButtonClick);
		}
		if (QuitButton)
		{
			QuitButton->OnClicked.AddDynamic(GameInstance, &UTowerHopGameInstance::QuitGame);
		}
		UpdateGraphicsButtonText();
	}
}

void UMainMenuWidget::OnGraphicsButtonClick()
{
	if (!GameInstance) return;

	GameInstance->CycleGraphicsQuality();
	UpdateGraphicsButtonText();
}

void UMainMenuWidget::UpdateGraphicsButtonText()
{
	if (!GameInstance || !GraphicsButtonText) return;

	FText text = FText::FromString("Quality: " + GameInstance->GraphicsQualityText());
	GraphicsButtonText->SetText(text);
}
